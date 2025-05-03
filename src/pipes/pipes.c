/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:11:48 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/03 15:26:18 by mmarinov         ###   ########.fr       */
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
		if (handle_redirections(cmd) < 0)
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

void	execute_piped_commands(t_cmd *cmd_list, t_shell *shell)
{
	int		pipefd[2];
	int		prev_fd;
	pid_t	pid;
	t_cmd	*curr;

	curr = cmd_list;
	prev_fd = -1;
	while (curr)
	{
		if (curr->next)
			pipe(pipefd);

		pid = fork();
		if (pid == 0)
		{
			if (prev_fd != -1)
				dup2(prev_fd, STDIN_FILENO);
			if (curr->next)
				dup2(pipefd[1], STDOUT_FILENO);
			if (prev_fd != -1)
				close(prev_fd);
			if (curr->next)
			{
				close(pipefd[0]);
				close(pipefd[1]);
			}
			// Redirecciones aquí: < > >> <<
			handle_redirections(curr);
			if (is_builtin_command(curr->cmd))
				handle_builtin_commands(curr, shell, NULL);
			else
				execute_single_command(curr, shell->env);
			exit(EXIT_FAILURE);
		}

		if (prev_fd != -1)
			close(prev_fd);
		if (curr->next)
		{
			close(pipefd[1]);
			prev_fd = pipefd[0];
		}
		curr = curr->next;
	}

	// Esperar todos los hijos
	curr = cmd_list;
	while (curr)
	{
		wait(NULL);
		curr = curr->next;
	}
}
