/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:47:00 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/18 14:27:46 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * free_env_list - Libera la lista de variables de entorno.
 * @env: Puntero a la lista de variables de entorno.
 */
void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		free(env);
		env = tmp;
	}
}

/**
 * ft_free_tokens - Libera la lista de tokens.
 * @tokens: Puntero a la lista de tokens.
 */
void	ft_free_tokens(t_tkn *tokens)
{
	t_tkn	*tmp;

	while (tokens)
	{
		tmp = tokens;
		if (tmp->value)
			free(tmp->value);
		tokens = tokens->next;
		free(tmp);
	}
}

/**
 * free_redirect_list - Libera la lista de redireccionamientos de un comando.
 * @redirect: Puntero a la lista de redireccionamientos.
 */
void	free_redirect_list(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		if (redir->file)
			free(redir->file);
		free(redir);
		redir = tmp;
	}
}

void	ft_free_list(t_cmd *cmd)
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
		if (tmp->redirects)
			free_redirect_list(tmp->redirects);
		free(tmp);
	}
}
