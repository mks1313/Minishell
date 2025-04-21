/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:15:12 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/21 13:15:16 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipe_data(t_pipe *pdata, t_cmd *cmds)
{
	int count = 0;

	while (cmds)
	{
		count++;
		cmds = cmds->next;
	}
	pdata->cmd_count = count;
	pdata->pids = malloc(sizeof(pid_t) * count);
}

void	close_unused_fds(t_pipe *pdata, int index)
{
	if (index > 0)
		close(pdata->prev_pipe);
	pdata->prev_pipe = pdata->fds[0];
	close(pdata->fds[1]);
}

int	wait_all(t_pipe *pdata)
{
	int	status = 0;
	int	i = 0;

	while (i < pdata->cmd_count)
	{
		waitpid(pdata->pids[i], &status, 0);
		i++;
	}
	return (WIFEXITED(status) ? WEXITSTATUS(status) : 1);
}
