/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 12:02:38 by mmarinov          #+#    #+#             */
/*   Updated: 2025/03/05 14:45:16 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/includes/libft.h"
#include "../../inc/minishell.h"

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

void handle_double_quotes(const char *inpt, char **envp)
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
					var_val = ft_getenv(var_name, envp);
					if (var_val)
						ft_printf("%s", var_val);
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

static int	count_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

void	expand_variable(const char *inpt, char **envp, int last_exit_status)
{
	int		i;
	int		var_start;
	char	var_name[256];
	char	*value;

	i = 0;
	while (inpt[i])
	{
		if (inpt[i] == '$')
		{
			i++;
			if (inpt[i] == '?')
			{
				ft_printf("%d", last_exit_status);
				i++;
			}
			else if (inpt[i] == '#')
			{
				ft_printf("%d", count_envp(envp));
				i++;
			}
			else if (inpt[i] == '$')
			{
				ft_printf("%d", ft_getpid());
				i++;
			}
			else if (ft_isalnum(inpt[i]) || inpt[i] == '_')
			{
				var_start = i;
				while (ft_isalnum(inpt[i]) || inpt[i] == '_')
					i++;
				ft_strncpy(var_name, &inpt[var_start], i - var_start);
				var_name[i - var_start] = '\0';
				value = ft_getenv(var_name, envp);
				if (value)
					ft_printf("%s", value);
			}
			else
			{
				ft_putchar('$');
				ft_putchar(inpt[i]);
				i++;
			}
		}
		else
		{
			ft_putchar(inpt[i]);
			i++;
		}
	}
	ft_putchar('\n');
}

void	process_input(const char *input, char **envp)
{
	int	last_exit_status;

	last_exit_status = 0;
	if (ft_strchr(input, '\''))
		handle_single_quotes(input);
	else if (ft_strchr(input, '"'))
		handle_double_quotes(input, envp);
	else
		expand_variable(input, envp, last_exit_status);
}
/*
int main(int ac, char **av, char **envp)
{
	char	*input;
	int		last_exit_status;

	last_exit_status = 0;
    (void)av;
	(void)ac;
	last_exit_status = 0;
	while (1)
	{
		input = readline("minishell> ");
		if (!input) // Manejo de Ctrl+D (EOF)
			break;
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			break;
		}
		process_input(input, envp);
		last_exit_status = (last_exit_status + 1) % 256;
		free(input);
	}
	return 0;
}*/
