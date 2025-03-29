/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:39:49 by meghribe          #+#    #+#             */
/*   Updated: 2025/03/29 17:38:25 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "exit") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "pwd") == 0)
		return (1);
	return (0);
}

static void	handle_commands(char *line, t_shell *shell, char **envp)
{
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
			handle_builtin_commands(tokens, shell, line);
			if (!is_builtin(tokens->value))
				handle_external_command(tokens, shell);
		}
		tokens = tokens->next;
	}
	ft_free_tokens(curr_tkn);
}

static void	lines(char *line, t_shell *shell, char **envp, int *last_exit_status)
{
	if (ft_strcmp(line, "exit") == 0)
	{
		free(line);
		return ;
	}
	if (*line)
	{
		add_history(line);
		handle_commands(line, shell, envp);
		*last_exit_status = (*last_exit_status + 1) % 256;
	}
	free(line);
}

static void	cleanup_and_exit(t_shell *shell)
{
	free_data(shell);
	ft_putstr_fd("exit\n", 2);
	clear_history();
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
			cleanup_and_exit(shell);
			return (0);
		}
		lines(line, shell, envp, &last_exit_status);
		if (ft_strcmp(line, "exit") == 0)
			break ;
	}
	free_data(shell);
	return (0);
}
