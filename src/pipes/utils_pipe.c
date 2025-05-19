/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:15:12 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/19 16:33:36 by mmarinov         ###   ########.fr       */
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
	}
	else
		shell->exit_status = 1;
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
