/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:14:34 by meghribe          #+#    #+#             */
/*   Updated: 2025/04/13 14:02:50 by mmarinov         ###   ########.fr       */
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

void	handle_builtin_commands(t_cmd *cmd, t_shell *shell, char *line)
{
	if (ft_strcmp(cmd->cmd, "exit") == 0)
	{
		ft_putstr_fd(RED"exit\n"RES, 1);
		free(line);
		ft_exit(cmd, shell);
	}
	else if (ft_strcmp(cmd->cmd, "env") == 0)
		ft_env(shell->env);
	else if (ft_strcmp(cmd->cmd, "cd") == 0)
		ft_cd(cmd, shell);
	else if (ft_strcmp(cmd->cmd, "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd->cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		ft_export(&shell->env, cmd);
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
		ft_unset(cmd, shell);
}

void	handle_external_command(t_cmd *cmd, t_shell *shell)
{
	char	**args;

	args = cmd->args;
	if (args)
	{
		shell->exit_status = exec_cmd(cmd->cmd, args, shell->env);
	}
}
