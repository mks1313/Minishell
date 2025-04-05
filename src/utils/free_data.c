/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:47:00 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/05 19:29:13 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * free_env_list - Libera la lista de variables de entorno.
 * @env: Puntero a la lista de variables de entorno.
 */
/*
void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}*/

/**
 * ft_free_tokens - Libera la lista de tokens.
 * @tokens: Puntero a la lista de tokens.
void	ft_free_tokens(t_tkn *tokens)
{
	t_tkn	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}
 */

/**
 * free_redirect_list - Libera la lista de redireccionamientos de un comando.
 * @redirect: Puntero a la lista de redireccionamientos.
 */
void	free_redirect_list(t_redirect *redirect)
{
	t_redirect	*tmp;

	while (redirect)
	{
		tmp = redirect->next;
		free(redirect->file);
		free(redirect);
		redirect = tmp;
	}
}

/**
 * free_cmd_list - Libera la lista de comandos y sus argumentos.
 * @cmd_list: Puntero a la lista de comandos.
void	free_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*tmp;
	int		i;

	while (cmd_list)
	{
		tmp = cmd_list->next;
		free(cmd_list->cmd);
		if (cmd_list->args)
		{
			i = 0;
			while (cmd_list->args[i])
				free(cmd_list->args[i++]);
			free(cmd_list->args);
		}
		free_redirect_list(cmd_list->redirect);
		free(cmd_list);
		cmd_list = tmp;
	}
}
 */

/**
 * free_data - Libera todas las estructuras de datos en el shell.
 * @shell: Estructura del shell que contiene todos los datos.
void	free_data(t_shell *shell)
{
	free_env_list(shell->env);
	ft_free_tokens(shell->tkns);
	free_cmd_list(shell->cmds);
	free(shell->cur_dir);
	free(shell);
}
 */
