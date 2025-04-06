/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:39:49 by meghribe          #+#    #+#             */
/*   Updated: 2025/04/06 17:00:50 by mmarinov         ###   ########.fr       */
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

/*static void	handle_commands(char *line, t_shell *shell, char **envp)
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
		if (tokens->type == TOK_WORD)
		{
			handle_builtin_commands(tokens, shell, line);
			if (!is_builtin(tokens->value))
				handle_external_command(tokens, shell);
		}
		tokens = tokens->next;
	}
	ft_free_tokens(curr_tkn);
}

//TODO mirar nuestro exit que pasa, tambien quitar shell
static void	lines(char *line, t_shell *shell, char **envp, int *l_e_s)
{
	if (ft_strcmp(line, "exit") == 0)
	{
		//free(line);
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
	clear_history();
}*/

int	main(int argc, char *argv[], char **envp)
{
	char	*line;
	int		l_e_s;

	(void)argc;
	(void)argv;
	l_e_s = 0;
	while (1)
	{
		line = readline(GREEN"minishell$ "RES);
		if (!line)
		{
			//cleanup_and_exit(shell);
			return (0);
		}
		//process_input(line, shell->env, l_e_s);
		//lines(line, shell, envp, &l_e_s);
		if (ft_strcmp(line, "exit") == 0)
			break ;
	}
	//free_data(shell);
	return (0);
}
