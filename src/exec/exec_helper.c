/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:28:07 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/20 12:43:51 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*check_cmd_path(char *cmd, t_env *env)
{
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	return (find_command_path(cmd, env));
}

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
