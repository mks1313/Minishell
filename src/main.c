/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:39:49 by meghribe          #+#    #+#             */
/*   Updated: 2025/04/05 20:07:55 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
// Esta comentada para no pasar por el error: 'is_builtin' defined but not ussed
static int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "exit") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0)
		return (1);
	return (0);
}*/

/*
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
}*/

//TODO mirar nuestro exit que pasa
/*
static void	lines(char *line, t_shell *shell, char **envp, int *l_e_s)
{
	//if (ft_strcmp(line, "exit") == 0)
	//{
			//free(line);
		//exit(EXIT_SUCCESS);
		//return ;
	//}
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
static void	frees(void)
{
}

void	executor() { }
void	ft_lexer(char *line, t_lexer *lexer) 
{
	(void)line;
	(void)lexer;
}

void	her_doc(t_cmd *cmd)
{ 
	(void)cmd;
}

int	ft_parse() { return (1);}
int	expansor() { return (1);}

int	main(int argc, char *argv[], char **envp)
{
	//t_shell	*shell;
	t_lexer	*lexer;
	t_env	*my_env;
	t_cmd	*cmd;
	char	*line;
	int		l_e_s;

	(void)argc;
	(void)argv;
	(void)envp;
	l_e_s = 0;
	//shell = init_shell();
	cmd = (t_cmd *)malloc(sizeof(t_cmd *));
	lexer = (t_lexer *)malloc(sizeof(t_lexer *));
	(void)my_env;
	(void)l_e_s;
	while (1)
	{
		line = readline(GREEN"minishell$ "RES);
		if (!line)
		{
			// cleanup_and_exit(shell);
			return (0);
		}
		ft_lexer(line, lexer);
		if (ft_parse()) // sin error parsing
		{
			her_doc(cmd);
			// TODO: Question --> Supongo que la palabra es expansor y no expandor, no?
			// TODO: ENVLIST Y MY_ENV??? ENVLIST debe ser envp? o otra copia nuestra?
			// TODO: NO BORRAR
			/*
			if (!expansor(*cmd, envlist))
			{
				executor(cmd, envlist, my_env);
			}*/
	
		}
		frees();
		//process_input(line, my_env, l_e_s);
		//lines(line, shell, envp, &l_e_s);
		if (ft_strcmp(line, "exit") == 0)
		{
			free(line);
			break ;
		}
	}
	free(lexer);
	free(cmd);
	//free(line);
	//free_data(shell);
	return (0);
}
