/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:11:48 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/21 15:57:46 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_single_command(t_cmd *cmd, t_env *env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (handle_redirections(cmd->redirects) < 0)
			exit(1);
		if (!cmd->args || !cmd->args[0])
			exit(0);
		exec_cmd(cmd->args[0], cmd->args, env);
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

	i = 0;
	pdata->prev_fd = -1; // inicializamos
	while (cmds)
	{
		if (cmds->next) // si hay otro comando después, creamos pipe nuevo
			pipe(pdata->fd);
		pid = fork();
		if (pid == 0)
			execute_child(cmds, pdata, i, env);
		else if (pid < 0)
			perror("fork");
		if (pdata->prev_fd != -1) // cerramos anterior si existe
			close(pdata->prev_fd);
		if (cmds->next) // si hay pipe, guardamos para el siguiente
			pdata->prev_fd = pdata->fd[0];
		close(pdata->fd[1]); // cerramos el write del pipe actual
		pdata->pids[i] = pid;
		cmds = cmds->next;
		i++;
	}
	status = wait_all(pdata);
	return (status);
}

int	execute_cmds(t_cmd *cmds, t_env *env)
{
	t_pipe	pipe_data;
	int		status;

	if (!cmds)
		return (1);
	init_pipe_data(&pipe_data, cmds);
	if (pipe_data.n_cmds == 1)
		return (execute_single_command(cmds, env));
	status = execute_piped_commands(cmds, &pipe_data, env);
	free_pipe_data(&pipe_data);
	return (status);
}
