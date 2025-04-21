/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:13:31 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/21 15:01:47 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_child(t_cmd *cmd, t_pipe *pdata, int index, t_env *env)
{
	// Si no es el primer comando, redirigimos stdin desde pipe anterior
	if (index > 0 && pdata->prev_fd != -1)
		dup2(pdata->prev_fd, STDIN_FILENO);
	// Si hay siguiente comando, redirigimos stdout al pipe actual
	if (cmd->next)
		dup2(pdata->fd[1], STDOUT_FILENO);
	// Cerramos pipes innecesarios en el hijo
	if (pdata->prev_fd != -1)
		close(pdata->prev_fd);
	if (cmd->next)
	{
		close(pdata->fd[0]);
		close(pdata->fd[1]);
	}
	if (handle_redirections(cmd->redirects) < 0)
		exit(1);
	if (!cmd->args || !cmd->args[0])
		exit(0);
	exec_cmd(cmd->args[0], cmd->args, env);
	exit(127); // si exec falla
}
