/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:39:49 by meghribe          #+#    #+#             */
/*   Updated: 2025/03/29 13:58:49 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_delimiters(char *str, const char *delimiters)
{
	while (*str && ft_strchr(delimiters, *str))
		str++;
	return (str);
}

// TODO: implementar bien los builtins
static void	handle_commands(char *line, t_shell *shell, char **envp)
{
	//int		last_exit_status;
	t_tkn	*tokens;
	t_tkn	*curr_tkn;

	(void)envp;
	if (!shell)
		return ;
	tokens = tokenize_input(line);
	if (!tokens)
		return ;
	curr_tkn = tokens;
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD)
		{
			if (ft_strcmp(tokens->value, "exit") == 0)
			{
				free(line);
				ft_free_tokens(curr_tkn);
				ft_exit(NULL);
			}
			else if (ft_strcmp(tokens->value, "env") == 0)
				ft_env(shell->env);
			else if (ft_strcmp(tokens->value, "cd") == 0)
				ft_cd(tokens, shell);
			else if (ft_strcmp(tokens->value, "echo") == 0)
				ft_echo(tokens);
			else if (ft_strcmp(tokens->value, "pwd") == 0)
				ft_pwd();
			else
			{
				char **args = tokens_to_args(tokens);
				if (args)
				{
					shell->exit_status = execute_external_command(tokens->value, args, shell->env);
					clean_array(args);
				}
			}
		}
		tokens = tokens->next;
	}
	ft_free_tokens(curr_tkn);
}

int	main(int argc, char *argv[], char **envp)
{
	t_shell	*shell;
	char	*line;
	int		last_exit_status;

	(void)argc;
	(void)argv;
	last_exit_status = 0;
	shell = init_shell();
	shell->env = convert_env(envp);
	while (1)
	{
		line = readline("minishell$ ");
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
