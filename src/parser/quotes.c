/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:35:52 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/01 18:33:55 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	single_quotes(const char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		ft_putchar(input[i]);
		if (input[i] == '\'')
		{
			i++;
			while (input[i] && input[i] != '\'')
				ft_putchar(input[i++]);
			if (input[i] == '\'')
				ft_putchar(input[i++]);
		}
		else
			i++;
	}
}

static void	print_var_value(char *var_name, t_env *env)
{
	char	*var_val;

	var_val = ft_getenv(var_name, env);
	if (var_val)
		ft_printf("%s", var_val);
}

static void	variable_in_quotes(const char *inpt, int *i, t_env *env, int l_e_s)
{
	int		j;
	char	var_name[256];

	(*i)++;
	if (inpt[*i] == '?')
	{
		ft_printf("%d", l_e_s);
		(*i)++;
		return ;
	}
	j = 0;
	while (inpt[*i] && (ft_isalnum(inpt[*i]) || inpt[*i] == '_'))
	{
		var_name[j++] = inpt[*i];
		(*i)++;
	}
	var_name[j] = '\0';
	print_var_value(var_name, env);
}

static void	chars_inside_quotes(const char *inpt, int *i, t_env *env, int l_e_s)
{
	if (inpt[*i] == '$')
		variable_in_quotes(inpt, i, env, l_e_s);
	else
	{
		ft_putchar(inpt[*i]);
		(*i)++;
	}
}

void	double_quotes(const char *inpt, t_env *env, int l_e_s)
{
	int	i;

	i = 0;
	while (inpt[i])
	{
		if (inpt[i] == '"')
		{
			i++;
			while (inpt[i] && inpt[i] != '"')
				chars_inside_quotes(inpt, &i, env, l_e_s);
			if (inpt[i] == '"')
				ft_putchar(inpt[i++]);
		}
		else
			i++;
	}
}
