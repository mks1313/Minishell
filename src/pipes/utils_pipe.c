/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:15:12 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/21 19:18:28 by mmarinov         ###   ########.fr       */
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

	printf("Initializing pie data~!\n");
	count = 0;
	while (cmds)
	{
		count++;
		cmds = cmds->next;
	}
	pdata->n_cmds = count;
	printf("Number of command: %d\n", pdata->n_cmds);
	pdata->pids = malloc(sizeof(pid_t) * count);
	if (!pdata->pids)
	{
		perror("malloc!!!");
		exit(1);
	}
	pdata->prev_fd = -1;
}

void	close_unused_fds(t_pipe *pdata)
{
	printf("Closing unused FD: %d\n", pdata->fd[0]);
	close(pdata->fd[0]);
	pdata->fd[0] = pdata->fd[1];
}

int	wait_all(t_pipe *pdata)
{
	int	i;
	int	status;
	int	last_status;

	printf("Waiting for all process to finish.\n");
	last_status = 0;
	i = 0;
	while (i < pdata->n_cmds)
	{
		printf("Waitinfg dfor proccess %d\n", i);
		status = 0;
		waitpid(pdata->pids[i], &status, 0);
		if (WIFEXITED(status))
		{
			last_status = WEXITSTATUS(status);
			printf("Process %d finished wth status %d\n", i, last_status);
		}
		i++;
	}
	return (last_status);
}
