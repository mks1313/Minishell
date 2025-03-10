/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:39:49 by meghribe          #+#    #+#             */
/*   Updated: 2025/03/10 18:40:35 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}*/

char	*skip_delimiters(char *str, const char *delimiters)
{
    while (*str && ft_strchr(delimiters, *str))
        str++;
    return (str);
}

static void	handle_commands(char *line, char **envp)
{
	t_shell	*shell;
	int		last_exit_status;
	t_tkn	*tokens;
	t_env	*env;

	shell = init_shell();
	if (!shell)
		return ;
	last_exit_status = 0;
	env = convert_env(envp);
	// Tokenización del input
	tokens = tokenize_input(line);
	if (!tokens)
		return ;
	// Procesamiento de los comandos
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD)
		{
			// Se maneja el comando
			if (ft_strcmp(tokens->value, "exit") == 0)
			{
				free(line);
				ft_exit(NULL);
			}
			else if (ft_strcmp(tokens->value, "env") == 0)
			{
				shell->env = convert_env(envp);
				ft_env(shell->env);
			}
			else if (ft_strcmp(tokens->value, "cd") == 0)
			{
				// Implementar cd aquí
				ft_cd(tokens, shell);
			}
			else if (ft_strcmp(tokens->value, "echo") == 0)
			{
				// Implementar echo aquí
				ft_echo(tokens);
			}
			else
			{
				// Expansión de variables y procesamiento de otras tareas
				expand_variable(line, env, last_exit_status);
				//handle_quotes(line);
			}
		}
		// Moverse al siguiente token
		tokens = tokens->next;
	}

	// Liberación de memoria
	ft_free_tokens(tokens);
	free(shell);
}

int	main(int argc, char *argv[], char *envp[])
{
	char				*line;
	//struct sigaction	sa;
	int					last_exit_status;

	(void)argc;
	(void)argv;
	last_exit_status = 0;
	//set_sig(&sa, handle_signal);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			ft_putstr_fd("exit\n", 2);
			clear_history();
			ft_exit(NULL);
		}
		if (ft_strcmp(line, "exit") == 0)
		{
			free(line);
			break ;
		}
		if (*line)
		{
			add_history(line);
			handle_commands(line, envp);
			last_exit_status = (last_exit_status + 1) % 256;
		}
		free(line);
	}
	return (0);
}
