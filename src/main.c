/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:39:49 by meghribe          #+#    #+#             */
/*   Updated: 2025/05/03 16:41:14 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

int	is_builtin_command(char *cmd)
{
	const char	*builtins[] = {"exit", "env", "cd", "echo",
		"pwd", "export", "unset", NULL};
	int			i;

	if (!cmd)
		return (0);
	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(cmd, builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

/*
static void debug(t_tkn *tkn)
{
	t_tkn *curr = tkn;
	while (curr)
	{
		printf("Token: %s | type: %d | sq: %d | dq: %d\n",
				curr->value, curr->type, curr->single_quote, curr->double_quote);
		curr = curr->next;
	}
}*/

static void	handle_commands(char *line, t_shell *shell)
{
	t_tkn	*tokens;
	t_cmd	*cmds;

	if (!shell || !line)
		return ;
	tokens = tokenize_input(line);
	if (!tokens)
		return ;
	lex_tokens(tokens);
	shell->tkns = tokens;
	expand_variable(shell);
	cmds = parse_tokens(tokens);
	if (!cmds)
	{
		ft_free_tokens(tokens);
		shell->tkns = NULL;
		return ;
	}
	shell->cmds = cmds;
	execute_commands(cmds, shell, line);
	ft_free_tokens(tokens);
	shell->tkns = NULL;
	free_cmd_list(cmds);
	shell->cmds = NULL;
}

static int	process_input_line(char **line_ptr, t_shell *shell)
{
	char	*line;

	line = readline(GREEN"minishell$ "RES);
	*line_ptr = line;
	if (!line)
		return (ft_putstr_fd("\nexit\n", 1), SHELL_EXIT);
	if (*line)
	{
		add_history(line);
		handle_commands(line, shell);
	}
	return (SHELL_CONTINUE);
}

static int	shell_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		if (process_input_line(&line, shell) == SHELL_EXIT)
			return (EXIT_SUCCESS);
		free(line);
	}
	return (EXIT_SUCCESS);
}

static int	clean_exit(t_shell *shell, int status)
{
	free_data(shell);
	rl_clear_history();
	return (status);
}

int	main(int argc, char *argv[], char **envp)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	set_signals();
	if (init_shell(&shell))
		return (EXIT_FAILURE);
	if (setup_environment(shell, envp))
		return (clean_exit(shell, EXIT_FAILURE));
	return (clean_exit(shell, shell_loop(shell)));
}
