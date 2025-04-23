/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:39:49 by meghribe          #+#    #+#             */
/*   Updated: 2025/04/23 15:13:16 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "exit") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0)
		return (1);
	return (0);
}

void	execute_commands(t_cmd *cmd, t_shell *shell, char *line)
{
	int		n_cmds;
	t_pipe	pipe_data;

	if (!cmd || !cmd->cmd)
		return ;

	n_cmds = count_cmds(cmd);
	if (n_cmds == 1)
	{
		if (is_builtin(cmd->cmd))
			handle_builtin_commands(cmd, shell, line);
		else
			execute_single_command(cmd, shell->env);
	}
	else
	{
		pipe_data.n_cmds = n_cmds;
		execute_piped_commands(cmd, &pipe_data, shell->env);
	}
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

static void	handle_commands(char *line, t_shell *shell, char **envp)
{
	t_tkn	*tokens;
	t_cmd	*cmds;

	(void)envp;
	if (!shell)
		return ;
	tokens = tokenize_input(line);
	if (!tokens)
		return ;
	lex_tokens(tokens);
	//debug(tokens);
	shell->tkns = tokens;
	expand_variable(shell);
	cmds = parse_tokens(tokens);
	if (!cmds)
	{
		ft_free_tokens(tokens);
		return ;
	}
	shell->cmds = cmds;
	execute_commands(cmds, shell, line);
	ft_free_tokens(tokens);
	ft_free_list(cmds);
}

int	main(int argc, char *argv[], char **envp)
{
	char	*line;
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = init_shell();
	shell->env = convert_env(envp);
	while (1)
	{
		line = readline(GREEN"minishell$ "RES);
		if (!line)
		{
			ft_putstr_fd("\nexit\n", 1);
			return (0);
		}
		if (*line)
		{
			add_history(line);
			handle_commands(line, shell, envp);
		}
		free(line);
	}
	free_data(shell);
	rl_clear_history();
	return (0);
}
