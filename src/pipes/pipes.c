/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:11:48 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/14 12:59:31 by mmarinov         ###   ########.fr       */
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
		if (handle_redirections(cmd) < 0)
			exit(1);
		if (!cmd->args || !cmd->args[0])
			exit(0);
		exec_cmd(cmd->args[0], cmd->args, env);
		exit(127);
	}
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

static void	child_process(t_cmd *curr, int prev_fd, int *pipefd, t_shell *shell)
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
	if (is_builtin_command(curr->cmd))
		handle_builtin_commands(curr, shell, NULL);
	else
		execute_single_command(curr, shell->env);
	exit(EXIT_FAILURE);
}

static pid_t	launch_child(t_cmd *curr, int *prev_fd, t_shell *shell)
{
	int		pipefd[2];
	pid_t	pid;

	if (curr->next && pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
		child_process(curr, *prev_fd, pipefd, shell);
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (*prev_fd != -1)
		close(*prev_fd);
	if (curr->next)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
	return (pid);
}

static void	wait_for_all(pid_t *pids, int n, t_shell *shell)
{
	int	status;
	int	i;

	i = 0;
	while (i < n)
	{
		if (waitpid(pids[i], &status, 0) != -1 && i == n - 1)
		{
			if (WIFEXITED(status))
				shell->exit_status = WEXITSTATUS(status);
			else
				shell->exit_status = 1;
		}
		i++;
	}
}

void	execute_piped_commands(t_cmd *cmd_list, t_shell *shell)
{
	t_cmd	*curr;
	int		prev_fd;
	int		i;
	int		n_cmds;
	pid_t	pids[256];

	curr = cmd_list;
	prev_fd = -1;
	i = 0;
	n_cmds = 0;
	while (curr)
	{
		pids[i] = launch_child(curr, &prev_fd, shell);
		if (pids[i] < 0)
			return ;
		curr = curr->next;
		i++;
	}
	n_cmds = i;
	wait_for_all(pids, n_cmds, shell);
}
