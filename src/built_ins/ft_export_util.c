/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:18:41 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/13 15:29:49 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_or_append_env(t_env **env, const char *key, const char *value)
{
	t_env	*var;
	t_env	*new;

	var = find_env(*env, key);
	if (var)
	{
		free(var->value);
		if (value)
			var->value = ft_strdup(value);
		else
			var->value = NULL;
	}
	else
	{
		new = malloc(sizeof(t_env));
		if (!new)
			error_exit("MALLOC FAILED!", 1);
		new->key = ft_strdup(key);
		if (value)
			new->value = ft_strdup(value);
		else
			new->value = NULL;
		new->next = *env;
		*env = new;
	}
}
