/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:47:00 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/10 13:46:08 by mmarinov         ###   ########.fr       */
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
		if (env->key != NULL)
			free(env->key);
		if (env->value != NULL)
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
		if (redir->delimiter)
			free(redir->delimiter);
		free(redir);
		redir = tmp;
	}
}

/**
 * free_cmd_list - frees the list of commands and the args
 * @cmd: Pointer ot the list
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
				free(tmp->args[i++]);
			free(tmp->args);
		}
		if (tmp->redirs)
			free_redirect_list(tmp->redirs);
		free(tmp);
	}
}

/**
 * free_data - Libera todas las estructuras de datos en el shell.
 * @shell: Estructura del shell que contiene todos los datos.
 */
void	free_data(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->env)
	{
		free_env_list(shell->env);
		shell->env = NULL;
	}
	if (shell->tkns)
	{
		ft_free_tokens(shell->tkns);
		shell->tkns = NULL;
	}
	if (shell->cmds)
	{
		free_cmd_list(shell->cmds);
		shell->cmds = NULL;
	}
	free(shell);
	shell = NULL;
}
