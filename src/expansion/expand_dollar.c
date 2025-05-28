/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:58:04 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/28 20:48:01 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Expands the exit status by returning it as a string.
 */
static char	*expand_exit_status(int *i)
{
	(*i)++;
	return (ft_itoa(g_exit_status));
}

/**
 * Expands an environment variable by looking it up in the shell’s environment.
 */
static char	*expand_env_variable(char *value, int *i, t_shell *shell)
{
	char	*expanded;

	expanded = handle_env_variable(value, i, shell->env);
	return (expanded);
}

/**
 * Expands the process ID by returning it as a string.
 */
static char	*expand_pid(int *i)
{
	char	*expanded;

	expanded = ft_itoa(ft_get_pid());
	(*i)++;
	return (expanded);
}

/**
 * Expands an unknown variable by appending the dollar sign
 * and the next character.
 */
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

/**
 * Handles the expansion of a dollar sign in a string.
 * It can expand exit status, environment variables, PID, or unknown variables.
 */
char	*handle_dollar_sign(char *value, int *i, t_shell *shell)
{
	if (is_empty_quoted_var(value, *i))
	{
		(*i)++;
		return (ft_strdup(""));
	}
	(*i)++;
	if (value[*i] == '?')
		return (expand_exit_status(i));
	else if (ft_isalnum(value[*i]) || value[*i] == '_')
		return (expand_env_variable(value, i, shell));
	else if (value[*i] == '$')
		return (expand_pid(i));
	else
		return (expand_unknown(value, i));
}
