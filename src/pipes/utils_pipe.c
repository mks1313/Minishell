/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:15:12 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/26 18:21:23 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_exit_status(int status, t_shell *shell)
{
	int	sig;

	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
		shell->exit_status = 128 + sig;
		g_exit_status = 128 + sig;
	}
	else
	{
		shell->exit_status = 1;
		g_exit_status = 1;
	}
}

void	wait_for_all(pid_t *pids, int n, t_shell *shell)
{
	int		status;
	pid_t	pid;
	int		i;
	pid_t	last_pid;

	last_pid = pids[n - 1];
	i = 0;
	while (i < n)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == last_pid)
			update_exit_status(status, shell);
		i++;
	}
}

bool	has_redirection_conflict(t_cmd *cmd_list)
{
	t_cmd	*a;
	t_cmd	*b;
	t_redir	*ra;
	t_redir	*rb;

	for (a = cmd_list; a; a = a->next)
	{
		for (ra = a->redirs; ra; ra = ra->next)
		{
			if (ra->type != REDIR_OUT && ra->type != REDIR_APPEND)
				continue;
			for (b = cmd_list; b; b = b->next)
			{
				if (b == a)
					continue;
				for (rb = b->redirs; rb; rb = rb->next)
				{
					if ((rb->type == REDIR_IN || rb->type == REDIR_HEREDOC)
						&& ft_strcmp(ra->file, rb->file) == 0)
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

t_cmd	*find_first_writer(t_cmd *cmd_list)
{
	t_cmd	*curr;
	t_redir	*r;

	curr = cmd_list;
	while (curr)
	{
		r = curr->redirs;
		while (r)
		{
			if (r->type == REDIR_OUT || r->type == REDIR_APPEND)
				return curr;
			r = r->next;
		}
		curr = curr->next;
	}
	return NULL;
}

int	execute_single_command(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
		child_process(cmd, -1, NULL, shell);
	if (pid < 0)
		return (perror("fork"), -1);
	waitpid(pid, &status, 0);
	return (WIFEXITED(status) ? WEXITSTATUS(status) : 1);
}
