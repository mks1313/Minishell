/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:39:49 by meghribe          #+#    #+#             */
/*   Updated: 2025/04/10 16:00:45 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "exit") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0)
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

//TODO mirar nuestro exit que pasa, tambien quitar shell
static void	lines(char *line, t_shell *shell, char **envp, int *l_e_s)
{
	if (ft_strcmp(line, "exit") == 0)
	{
		//free(line);
		ft_printf("Estoy en lines functions!\n");
		exit(EXIT_SUCCESS);
		return ;
	}
	if (*line)
	{
		add_history(line);
		handle_commands(line, shell, envp);
		*l_e_s = (*l_e_s + 1) % 256;
	}
	free(line);
}

static void	cleanup_and_exit(t_shell *shell)
{
	free_data(shell);
	rl_clear_history();
	clear_history();
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
			cleanup_and_exit(shell);
			return (0);
		}
		process_input(line, shell->env, l_e_s);
		lines(line, shell, envp, &l_e_s);
	}
	free_data(shell);
	rl_clear_history();
	return (0);
}
