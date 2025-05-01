/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:11:48 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/23 15:10:09 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_single_command(t_cmd *cmd, t_env *env)
{
	pid_t	pid;
	int		status;

	//printf("Execute single command: %s\n", cmd->cmd);
	pid = fork();
	if (pid == 0)
	{
		//printf("Child command: %s\n", cmd->cmd);
		if (handle_redirections(cmd->redirects) < 0)
		{
			//printf("Redireccion err for cmd: %s\n", cmd->cmd);
			exit(1);
		}
		if (!cmd->args || !cmd->args[0])
		{
			//printf("No args provided for cmd: %s\n", cmd->cmd);
			exit(0);
		}
		exec_cmd(cmd->args[0], cmd->args, env);
		//printf("Exec failed fo cmd: %s\n", cmd->cmd);
		exit(127);
	}
	else if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	execute_piped_commands(t_cmd *cmds, t_pipe *pdata, t_env *env)
{
	int		i;
	pid_t	pid;
	int		status;

	//printf("Starting piped commands!\n");
	i = 0;
	pdata->prev_fd = -1; // inicializamos
	while (cmds)
	{
		//printf("Perocessing cmd %d: %s\n", i + 1, cmds->cmd);
		if (cmds->next) // si hay otro comando después, creamos pipe nuevo
		{
			pipe(pdata->fd);
			//printf("Created pipe %d -> %d\n", pdata->fd[0], pdata->fd[1]);
		}
		pid = fork();
		if (pid == 0)
		{
			execute_child(cmds, pdata, i, env);
		//	printf("Child proccess for command: %s\n", cmds->cmd);
		}
		else if (pid < 0)
			perror("fork");
		if (pdata->prev_fd != -1) // cerramos anterior si existe
			{
		//	printf("Closing previos pipe: %d\n", pdata->prev_fd);
			close(pdata->prev_fd);
			}
		if (cmds->next) // si hay pipe, guardamos para el siguiente
		{
			pdata->prev_fd = pdata->fd[0];
		//	printf("Next command will use prev pipe: %d\n", pdata->prev_fd);
		}
		close(pdata->fd[1]); // cerramos el write del pipe actual
		//printf("Closed write  end of curr pipe %d\n", pdata->fd[1]);
		if (i >= pdata->n_cmds)
		{
			//fprintf(stderr, "ERROR: acceso fuera de los lim en pids[%d] (n_cmds = %d\n)", i, pdata->n_cmds);
		}
		pdata->pids[i] = pid;
		cmds = cmds->next;
		i++;
	}
	status = wait_all(pdata);
	//printf("Piped cmds executed, final status %d\n", status);
	return (status);
}

int	execute_cmds(t_cmd *cmds, t_env *env)
{
	t_pipe	pipe_data;
	int		status;

	if (!cmds)
		return (1);
	init_pipe_data(&pipe_data, cmds);
	//printf("Ejecutando %d comandos.\n", pipe_data.n_cmds);
	if (pipe_data.n_cmds == 1)
		return (execute_single_command(cmds, env));
	status = execute_piped_commands(cmds, &pipe_data, env);
	free_pipe_data(&pipe_data);
	return (status);
}
