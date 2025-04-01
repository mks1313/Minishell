/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:14:34 by meghribe          #+#    #+#             */
/*   Updated: 2025/04/01 18:49:25 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(const char *msg, int exit_code)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd(RES, 2);
	exit(exit_code);
}

char	*skip_delimiters(char *str, const char *delimiters)
{
	while (*str && ft_strchr(delimiters, *str))
		str++;
	return (str);
}

//TODO revisar este if, de exit, porque no se cumple . mirar bien
void	handle_builtin_commands(t_tkn *tokens, t_shell *shell, char *line)
{
	if (ft_strcmp(tokens->value, "exit") == 0)
	{
		printf("A ver este if sirve de algo???");
		free(line);
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
	else if (ft_strcmp(tokens->value, "export") == 0)
		ft_export(&shell->env, tokens);
	else if (ft_strcmp(tokens->value, "unset") == 0)
		ft_unset(tokens, shell);
}

void	handle_external_command(t_tkn *tokens, t_shell *shell)
{
	char	**args;

	args = tokens_to_args(tokens);
	if (args)
	{
		shell->exit_status = exec_cmd(tokens->value, args, shell->env);
		clean_array(args);
	}
}
