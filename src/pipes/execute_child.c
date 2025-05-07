/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:13:31 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/07 11:50:37 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Si no es el primer comando, redirigimos stdin desde pipe anterior
// Si hay siguiente comando, redirigimos stdout al pipe actual
// Cerramos pipes innecesarios en el hijo
void	execute_child(t_cmd *cmd, t_pipe *pdata, int index, t_env *env)
{
	if (index > 0 && pdata->prev_fd != -1)
		dup2(pdata->prev_fd, STDIN_FILENO);
	if (cmd->next)
		dup2(pdata->fd[1], STDOUT_FILENO);
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
	exit(127); 
}
