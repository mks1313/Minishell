/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:14:34 by meghribe          #+#    #+#             */
/*   Updated: 2025/05/20 11:01:13 by mmarinov         ###   ########.fr       */
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

bool	syntax_error(t_shell *shell, const char *msg, t_tkn_type type)
{
	if (msg)
		ft_putstr_fd(msg, STDERR_FILENO);
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token ", \
			STDERR_FILENO);
		ft_putstr_fd(get_token_name(type), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	shell->exit_status = 2;
	return (false);
}

void	skip_delimiters(char **str)
{
	while (**str && ft_strchr(" \t\r\n", **str))
		(*str)++;
}

int	handle_builtin_commands(t_cmd *cmd, t_shell *shell, char *line)
{
	(void)line;
	if (ft_strcmp(cmd->cmd, "exit") == 0)
	{
		ft_putstr_fd(RED"exit\n"RES, 1);
		ft_exit(cmd, shell);
	}
	if (ft_strcmp(cmd->cmd, "env") == 0)
	{
		if (cmd->args[1] != NULL)
			return (1);
		return (ft_env(shell->env));
	}
	if (ft_strcmp(cmd->cmd, "cd") == 0)
		return (ft_cd(cmd, shell));
	if (ft_strcmp(cmd->cmd, "echo") == 0)
		return (ft_echo(cmd));
	if (ft_strcmp(cmd->cmd, "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(cmd->cmd, "export") == 0)
		return (ft_export(&shell->env, cmd));
	if (ft_strcmp(cmd->cmd, "unset") == 0)
		return (ft_unset(cmd, shell));
	return (1);
}

int	handle_external_command(t_cmd *cmd, t_shell *shell)
{
	char	**args;
	int		status;

	args = cmd->args;
	if (!args)
		return (1);
	else
		status = exec_cmd(cmd->cmd, args, shell->env);
	return (status);
}
