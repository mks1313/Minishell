/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:11:48 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/19 16:33:21 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_external_cmd(t_cmd *curr, t_shell *shell)
{
	char	*cmd_path;
	char	**envp;

	if (handle_redirections(curr) < 0)
		exit(1);
	if (!curr->args || !curr->args[0])
		exit(0);
	cmd_path = find_command_path(curr->args[0], shell->env);
	if (!cmd_path)
	{
		ft_putstr_fd(curr->args[0], 2);
		ft_putstr_fd(ERR_CMD_NOT_FOUND, 2);
		exit(127);
	}
	envp = env_to_array(shell->env);
	execve(cmd_path, curr->args, envp);
	perror(curr->args[0]);
	clean_array(envp);
	free(cmd_path);
	exit(127);
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
		exit(handle_builtin_commands(curr, shell, NULL));
	else
		exec_external_cmd(curr, shell);
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
