/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:17:36 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/16 13:21:59 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * free_cmd_list - Libera la lista de comandos y sus argumentos.
 * @cmd_list: Puntero a la lista de comandos.
 */
void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->args)
		{
			i = 0;
			while (tmp->args[i])
			{
				free(tmp->args[i]);
				i++;
			}
			free(tmp->args);
		}
		free_redirect_list(tmp->redirects);
		free(tmp);
	}
}

/**
 * free_data - Libera todas las estructuras de datos en el shell.
 * @shell: Estructura del shell que contiene todos los datos.
 */
void	free_data(t_shell *shell)
{
	if (shell->env)
		free_env_list(shell->env);
	if (shell->tkns)
		ft_free_tokens(shell->tkns);
	if (shell->cmds)
		free_cmd_list(shell->cmds);
	if (shell->cur_dir)
		free(shell->cur_dir);
	if (shell)
		free(shell);
}
