/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 12:02:38 by mmarinov          #+#    #+#             */
/*   Updated: 2025/03/29 18:55:06 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_variable(const char *input, int *i, t_env *env)
{
	int		var_start;
	char	var_name[256];
	char	*value;

	var_start = *i;
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		(*i)++;
	ft_strncpy(var_name, &input[var_start], *i - var_start);
	var_name[*i - var_start] = '\0';
	value = ft_getenv(var_name, env);
	if (value)
		ft_printf("%s", value);
}

static void	dollar(const char *input, int *i, t_env *env, int last_exit_status)
{
	if (input[*i] == '?')
		handle_exit_status(i, last_exit_status);
	else if (input[*i] == '#')
		handle_envp_count(i, env);
	else if (input[*i] == '$')
		handle_pid(i);
	else if (ft_isalnum(input[*i]) || input[*i] == '_')
		handle_variable(input, i, env);
	else
	{
		ft_putchar('$');
		ft_putchar(input[*i]);
		(*i)++;
	}
}

void	expand_variable(const char *input, t_env *env, int last_exit_status)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
			dollar(input, &i, env, last_exit_status);
		else
		{
			ft_putchar(input[i]);
			i++;
		}
	}
	ft_putchar('\n');
}
