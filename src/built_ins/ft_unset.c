/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:14:46 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/01 19:12:32 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_env_var(t_env **env, const char *key)
{
	t_env	*curr;
	t_env	*prev;

	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev) // Si no es el primer nodo
				prev->next = curr->next;
			else// Si es el primer nodo
				*env = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	ft_unset(t_tkn *tokens, t_shell *shell)
{
	t_tkn	*curr_tkn;

	if (!tokens || !tokens->next)
	{
		ft_putstr_fd(RED"unset: too few arguments\n"RES, 2);
		return ;
	}
	curr_tkn = tokens->next;// Saltamos el "unset" y comenzamos con el  arg
	while (curr_tkn)
	{
		remove_env_var(&shell->env, curr_tkn->value);
		curr_tkn = curr_tkn->next;// Avanzamos al siguiente token
	}
}
