/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 12:02:38 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/05 13:30:12 by mmarinov         ###   ########.fr       */
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
	if (*i - var_start == 0)
	{
		ft_putchar('$');
		return ;
	}
	ft_strncpy(var_name, &input[var_start], *i - var_start);
	var_name[*i - var_start] = '\0';
	value = ft_getenv(var_name, env);
	if (value)
		ft_printf("%s", value);
	else
		ft_printf("");
}

static void	dollar(const char *input, int *i, t_env *env, int l_e_s)
{
	(*i)++;
	if (input[*i] == '?')
	{
		ft_printf("%d", l_e_s);
		(*i)++;
	}
	else if (ft_isalnum(input[*i]) || input[*i] == '_')
		handle_variable(input, i, env);
	else
	{
		(*i)++;
	}
}

void	expand_variable(const char *input, t_env *env, int l_e_s)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
			dollar(input, &i, env, l_e_s);
		else
		{
			ft_putchar(input[i]);
			i++;
		}
	}
}
