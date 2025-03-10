/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:14:34 by meghribe          #+#    #+#             */
/*   Updated: 2025/03/10 17:11:02 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(const char *msg, int exit_code)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd(RES, 2);
	exit(exit_code);
}

void	del(void *content)
{
	free(content);
}

void	ft_free_tokens(t_tkn *tokens)
{
	t_tkn	*tmp;
	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);  // Liberar los valores de los tokens
		free(tmp);         // Liberar el propio token
	}
}

void	free_data(t_shell *shell)
{
	t_env	*env;
	t_env	*tmp_env;
	t_tkn	*tkn;
	t_tkn	*tmp_tkn;
	t_cmd	*cmd_list;
	t_cmd	*tmp_cmd;

	// Liberar la lista de variables de entorno
	env = shell->env;
	tkn = shell->tkns;
	cmd_list = shell->cmds;
	while (env)
	{
		tmp_env = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp_env;
	}
	// Liberar la lista de tokens
	while (tkn)
	{
		tmp_tkn = tkn->next;
		free(tkn->value);
		free(tkn);
		tkn = tmp_tkn;
	}
	// Liberar la lista de comandos
	while (cmd_list)
	{
		tmp_cmd = cmd_list->next;
		free(cmd_list->cmd);
		if (cmd_list->args)
		{
			for (int i = 0; cmd_list->args[i]; i++)
				free(cmd_list->args[i]);
			free(cmd_list->args);
		}
		if (cmd_list->redirect)
		{
			t_redirect *tmp_redirect;
			t_redirect *redirect = cmd_list->redirect;
			while (redirect)
			{
				tmp_redirect = redirect->next;
				free(redirect->file);
				free(redirect);
				redirect = tmp_redirect;
			}
		}
		free(cmd_list);
		cmd_list = tmp_cmd;
	}
	// Liberar el directorio actual
	free(shell->cur_dir);
	// Finalmente liberar la estructura de datos
	free(shell);
}
