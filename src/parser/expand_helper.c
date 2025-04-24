/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:33:11 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/24 19:17:06 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_exit_status(int exit_status)
{
	char	*tmp;

	tmp = ft_itoa(exit_status);
	return (tmp);
}

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

static char	*expand_pid(void)
{
	pid_t	pid;

	pid = ft_get_pid();
	return (ft_itoa(pid));
}

char	*append_doll_and_char(char *expanded, char next_char)
{
	char	tmp[2];
	char	*aux;

	tmp[0] = next_char;
	tmp[1] = '\0';
	aux = ft_strjoin(expanded, tmp);
	free(expanded);
	return (aux);
}

char	*handle_dollar_sign(char *value, int *i, t_shell *shell)
{
	char	*expanded;

	(*i)++;
	if (value[*i] == '?')
	{
		expanded = handle_exit_status(shell->exit_status);
		(*i)++;
	}
	else if (ft_isalnum(value[*i]) || value[*i] == '_')
		expanded = handle_env_variable(value, i, shell->env);
	else if (value [*i] == '$')
	{
		expanded = expand_pid();
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
