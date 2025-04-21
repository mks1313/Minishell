/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:11:48 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/21 13:33:16 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_piped_commands(t_cmd *cmds, t_pipe *pdata, t_env *env)
{
	int		i;
	pid_t	pid;
	int		status;

	i = 0;
	while (cmds)
	{
		if (i < pdata->n_cmds - 1)
			pipe(pdata->fd);
		pid = fork();
		if (pid == 0)
			execute_child(cmds, pdata, i, env);
		else if (pid < 0)
			perror("fork");
		close_unused_fds(pdata, i);
		pdata->pids[i] = pid;
		cmds = cmds->next;
		i++;
	}
	status = wait_all(pdata);
	return (status);
}
