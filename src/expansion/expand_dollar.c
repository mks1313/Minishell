/* ************************************************************************** */
/*  expand_dollar                                                                          */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:13:20 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/20 19:57:41 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_exit_status(int *i, t_shell *shell)
{
	char	*expanded;

	expanded = ft_itoa(shell->exit_status);
	(*i)++;
	return (expanded);
}

static char	*expand_env_variable(char *value, int *i, t_shell *shell)
{
	char	*expanded;

	expanded = handle_env_variable(value, i, shell->env);
	return (expanded);
}

static char	*expand_pid(int *i)
{
	char	*expanded;

	expanded = ft_itoa(ft_get_pid());
	(*i)++;
	return (expanded);
}

static char	*expand_unknown(char *value, int *i)
{
	char	*expanded;

	expanded = ft_strdup("$");
	if (value[*i])
	{
		expanded = append_doll_and_char(expanded, value[*i]);
		(*i)++;
	}
	return (expanded);
}

char	*handle_dollar_sign(char *value, int *i, t_shell *shell)
{
	if (is_empty_quoted_var(value, *i))
	  {
	  (*i)++;
	  return (ft_strdup(""));
	  }
	(*i)++;
	if (value[*i] == '?')
		return (expand_exit_status(i, shell));
	else if (ft_isalnum(value[*i]) || value[*i] == '_')
		return (expand_env_variable(value, i, shell));
	else if (value[*i] == '$')
		return (expand_pid(i));
	else
		return (expand_unknown(value, i));
}
