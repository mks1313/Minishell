/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 12:02:38 by mmarinov          #+#    #+#             */
/*   Updated: 2025/03/10 18:57:56 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_single_quotes(const char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			i++;
			while (input[i] && input[i] != '\'')
			{
				ft_putchar(input[i]);
				i++;
			}
			i++;
		}
		else
		{
			ft_putchar(input[i]);
			i++;
		}
	}
}

void	handle_double_quotes(const char *inpt, t_env *env)
{
	int		i;
	int		j;
	char	var_name[256];
	char	*var_val;

	i = 0;
	while (inpt[i])
	{
		if (inpt[i] == '"')
		{
			i++;
			while (inpt[i] && inpt[i] != '"')
			{
				if (inpt[i] == '$')
				{
					i++;
					j = 0;
					while (inpt[i] && (ft_isalnum(inpt[i]) || inpt[i] == '_'))
						var_name[j++] = inpt[i++];
					var_name[j] = '\0';
					var_val = ft_getenv(var_name, env);// Expan de var
					if (var_val)
						ft_printf("%s", var_val);
					else
						ft_printf("");// Imprime nada si no se encuentra la vari
				}
				else
				{
					ft_putchar(inpt[i]);
					i++;
				}
			}
			i++;
		}
		else
		{
			ft_putchar(inpt[i]);
			i++;
		}
	}
}

int	count_envp(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return count;
}

void	expand_variable(const char *input, t_env *env, int last_exit_status)
{
	int		i;
	int		var_start;
	char	var_name[256];
	char	*value;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			i++;
			if (input[i] == '?')
			{
				ft_printf("%d", last_exit_status);
				i++;
			}
			else if (input[i] == '#')
			{
				ft_printf("%d", count_envp(env));
				i++;
			}
			else if (input[i] == '$')
			{
				ft_printf("%d", getpid());
				i++;
			}
			else if (ft_isalnum(input[i]) || input[i] == '_')
			{
				var_start = i;
				while (ft_isalnum(input[i]) || input[i] == '_')
					i++;
				ft_strncpy(var_name, &input[var_start], i - var_start);
				var_name[i - var_start] = '\0';
				value = ft_getenv(var_name, env);
				if (value)
					ft_printf("%s", value);
			}
			else
			{
				ft_putchar('$');
				ft_putchar(input[i]);
				i++;
			}
		}
		else
		{
			ft_putchar(input[i]);
			i++;
		}
	}
	ft_putchar('\n');
}

void	process_input(const char *input, t_env *env)
{
	int	last_exit_status;

	last_exit_status = 0;
	if (ft_strchr(input, '\''))
		handle_single_quotes(input);
	else if (ft_strchr(input, '"'))
		handle_double_quotes(input, env);
	else
		expand_variable(input, env, last_exit_status);
}
