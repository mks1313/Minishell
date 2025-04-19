/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:39:49 by meghribe          #+#    #+#             */
/*   Updated: 2025/04/18 17:30:31 by mmarinov         ###   ########.fr       */
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
	t_cmd	*curr;

	curr = cmd;
	while (curr)
	{
		if (curr->cmd)
		{
			if (is_builtin(curr->cmd))
				handle_builtin_commands(curr, shell, line);
			else
				handle_external_command(curr, shell);
		}
		curr = curr->next;
	}
}

/*static void debug_print_tokens(t_tkn *tokens)
{
    t_tkn *current = tokens;
    while (current)
    {
        printf("Token: %s, Type: %d\n", current->value, current->type);
        current = current->next;
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
	int		l_e_s;
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = init_shell();
	shell->env = convert_env(envp);
	l_e_s = 0;
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
			l_e_s = (l_e_s + 1) % 256;
		}
		free(line);
	}
	free_data(shell);
	rl_clear_history();
	return (0);
}
