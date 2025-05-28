/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:28:07 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/28 13:14:16 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Executes a single command, handling redirections first.
 * If redirections succeed, it dispatches builtins or external commands.
 */
void	execute_single_command(t_cmd *cmd, t_shell *shell, char *line)
{
	if (handle_redirections(cmd) < 0)
	{
		shell->exit_status = 1;
		g_exit_status = 1;
		return ;
	}
	if (is_builtin_command(cmd->cmd))
		shell->exit_status = handle_builtin_commands(cmd, shell, line);
	else
		shell->exit_status = handle_external_command(cmd, shell);
}

/**
 * Handles commands that only contain redirections and no actual command.
 * Updates the shell's exit status depending on the redirection result.
 * Returns 0 if success, -1 if redirection failed.
 */
int	handle_redir_only_command(t_cmd *cmd, t_shell *shell)
{
	int	res;

	res = handle_redirections(cmd);
	if (res < 0)
	{
		shell->exit_status = 1;
		g_exit_status = 1;
	}
	else
	{
		shell->exit_status = 0;
		g_exit_status = 0;
	}
	return (res);
}

/**
 * Checks if the command is "." or ".." and handles errors accordingly.
 * Returns 2 for missing argument, 127 for ".." not found.
 **/
int	check_dot_dot_cmd(char *cmd)
{
	if (ft_strcmp(cmd, ".") == 0)
	{
		ft_putstr_fd("minishell: .: filename arg required\n", STDERR_FILENO);
		ft_putstr_fd(".: usage: . filename [arguments]\n", STDERR_FILENO);
		return (2);
	}
	if (ft_strcmp(cmd, "..") == 0)
	{
		ft_putstr_fd("minishell: ..: command not found\n", STDERR_FILENO);
		return (127);
	}
	return (0);
}

/**
 * Checks if the command contains a slash. If so, duplicates it.
 * Otherwise, tries to resolve its path from the PATH variable.
 **/
char	*check_cmd_path(char *cmd, t_env *env)
{
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	return (find_command_path(cmd, env));
}

/**
 * Validates that the given path is not a directory.
 * Returns 126 for directory, 127 for stat error, 0 if valid.
 **/
int	validate_cmd(char *cmd_path)
{
	int	res;

	res = is_directory(cmd_path);
	if (res == 1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd_path, STDERR_FILENO);
		ft_putstr_fd(ERR_IS_DIR, STDERR_FILENO);
		return (126);
	}
	else if (res == -1)
	{
		perror("minishell");
		return (127);
	}
	return (0);
}
