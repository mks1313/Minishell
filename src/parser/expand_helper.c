/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:33:11 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/03 19:30:44 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_env_variable(char *value, int *i, t_env *env)
{
	int		start;
	char	*tmp;
	char	*val;

	start = *i;
	while (ft_isalnum(value[*i]) || value[*i] == '_')
		(*i)++;
	tmp = ft_substr(value, start, *i - start);
	val = ft_getenv(tmp, env);
	free(tmp);
	if (val)
		return (ft_strdup(val));
	else
		return (ft_strdup(""));
}

char	*append_doll_and_char(char *expanded, char next_char)
{
	char	tmp[2];
	char	*aux;

	tmp[0] = next_char;
	tmp[1] = '\0';
	aux = ft_strjoin(expanded, tmp);
	return (free(expanded), aux);
}

char	*handle_dollar_sign(char *value, int *i, t_shell *shell)
{
	char	*expanded;

	(*i)++;
	if (value[*i] == '?')
	{
		expanded = ft_itoa(shell->exit_status);
		(*i)++;
	}
	else if (ft_isalnum(value[*i]) || value[*i] == '_')
		expanded = handle_env_variable(value, i, shell->env);
	else if (value [*i] == '$')
	{
		expanded = ft_itoa(ft_get_pid());
		(*i)++;
	}
	else
	{
		expanded = ft_strdup("$");
		if (value[*i])
		{
			expanded = append_doll_and_char(expanded, value[*i]);
			(*i)++;
		}
	}
	return (expanded);
}
