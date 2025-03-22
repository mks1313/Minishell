/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:39:49 by meghribe          #+#    #+#             */
/*   Updated: 2025/03/22 14:00:22 by mmarinov         ###   ########.fr       */
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

static void	handle_commands(char *line, t_shell *shell, char **envp)
{
	int		last_exit_status;
	t_tkn	*tokens;
	t_tkn	*curr_tkn;
	//t_env	*env;
	(void)envp;

	if (!shell)
		return ;
	last_exit_status = 0;
	//env = convert_env(envp);
	// Tokenización del input
	tokens = tokenize_input(line);
	if (!tokens)
		return ;
	// Procesamiento de los comandos
	curr_tkn = tokens;
	while (tokens)
	{
		ft_printf("Token value ==> %s", tokens->value);
		if (tokens->type == TOKEN_WORD)
		{
			// Se maneja el comando
			if (ft_strcmp(tokens->value, "exit") == 0)
			{
				free(line);
                ft_free_tokens(curr_tkn);
				ft_exit(NULL);
			}
			else if (ft_strcmp(tokens->value, "env") == 0)
			{
				//shell->env = convert_env(envp);
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
				expand_variable(line, shell->env, last_exit_status);
				//handle_quotes(line);
			}
		}
		// Moverse al siguiente token
		tokens = tokens->next;
	}

	// Liberación de memoria
	ft_free_tokens(curr_tkn);
	//free(shell);
}

int	main(int argc, char *argv[], char **envp)
{
	t_shell	*shell;
	char				*line;
	//struct sigaction	sa;
	int					last_exit_status;

	(void)argc;
	(void)argv;
	last_exit_status = 0;
	//set_sig(&sa, handle_signal);
	//exit(EXIT_SUCCESS);
	shell = init_shell();
	shell->env = convert_env(envp);
	while (1)
	{
		line = readline("minishell$ ");
		//line = get_next_line(0);
		if (!line)
		{
			free_data(shell);
			ft_putstr_fd("exit\n", 2);
			clear_history();
			return (0);
		}
		if (ft_strcmp(line, "exit") == 0)
		{
			free(line);
			break ;
		}
		if (*line)
		{
			add_history(line);
			handle_commands(line, shell, envp);
			last_exit_status = (last_exit_status + 1) % 256;
		}
		free(line);
	}
	free_data(shell);
	return (0);
}
