/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:06:36 by mmarinov          #+#    #+#             */
/*   Updated: 2025/03/10 18:12:12 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*init_shell(void)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	// Inicialización de los valores de shell, si es necesario
	shell->env = NULL;
	shell->tkns = NULL;
	shell->cmds = NULL;
	shell->exit_status = 0;
	shell->cur_dir = NULL;
	return (shell);
}

t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = NULL; // Comando vacío al principio
	cmd->args = NULL; // Argumentos vacíos
	cmd->redirect = NULL; // Sin redirecciones
	cmd->is_pipe = false; // No hay tubería por defecto
	cmd->pipe_fds[0] = -1; // Inicializar el pipe fd[0]
	cmd->pipe_fds[1] = -1; // Inicializar el pipe fd[1]
	cmd->pid = 0; // Sin proceso hijo por defecto
	cmd->next = NULL; // El siguiente comando es NULL al principio
	return (cmd);
}

