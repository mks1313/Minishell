/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:15:12 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/21 15:55:39 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipe_data(t_pipe *pdata)
{
	if (pdata->pids)
		free(pdata->pids);
	pdata->pids = NULL;
}

int	count_cmds(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

void	init_pipe_data(t_pipe *pdata, t_cmd *cmds)
{
	int	count;

	count = 0;
	while (cmds)
	{
		count++;
		cmds = cmds->next;
	}
	pdata->n_cmds = count;
	pdata->pids = malloc(sizeof(pid_t) * count);
	pdata->prev_fd = -1;
}

void	close_unused_fds(t_pipe *pdata)
{
	close(pdata->fd[0]);
	pdata->fd[0] = pdata->fd[1];
}

int	wait_all(t_pipe *pdata)
{
	int	i;
	int	status;
	int	last_status;

	last_status = 0;
	i = 0;
	while (i < pdata->n_cmds)
	{
		waitpid(pdata->pids[i], &status, 0);
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		i++;
	}
	return (last_status);
}
