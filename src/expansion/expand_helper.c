/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:39:58 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/28 20:48:25 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Expands an environment variable by retrieving its
 * value from the shell’s environment.
 */
char	*handle_env_variable(char *value, int *i, t_env *env)
{
	int		start;
	char	*key;
	char	*val;

	start = *i;
	while (ft_isalnum(value[*i]) || value[*i] == '_')
		(*i)++;
	key = ft_substr(value, start, *i - start);
	val = ft_getenv(key, env);
	free(key);
	if (val)
		return (ft_strdup(val));
	else
		return (ft_strdup(""));
}

/**
 * Checks if the variable is an empty quoted variable (i.e., "$" inside quotes).
 */
bool	is_empty_quoted_var(const char *value, int i)
{
	return (value[i] == '$' && (value[i + 1] == '"' || value[i + 1] == '\''));
}
