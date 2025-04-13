/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:14:46 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/13 11:42:57 by mmarinov         ###   ########.fr       */
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
			if (prev)
				prev->next = curr->next;
			else
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

void	ft_unset(t_cmd *cmd, t_shell *shell)
{
	int	i;
	if (!cmd || !cmd->args || !cmd->args[0])
	{
		ft_putstr_fd(RED"unset: too few arguments\n"RES, 2);
		return ;
	}
	i = 0;
	while (cmd->args[i])
	{
		remove_env_var(&shell->env, cmd->args[i]);
		i++;
	}
}
