/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:12:00 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/17 15:29:18 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_child_process(char *cmd_path, char **args, t_env *env)
{
	char	**envp;

	envp = env_to_array(env);
	if (execve(cmd_path, args, envp) == -1)
		perror(cmd_path);
	clean_array(envp);
	free(cmd_path);
	exit(EXIT_FAILURE);
}

static int	wait_for_process(pid_t pid, char *cmd_path)
{
	int		status;

	waitpid(pid, &status, 0);
	free(cmd_path);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	exec_cmd(char *cmd, char **args, t_env *env)
{
	char	*cmd_path;
	pid_t	pid;
	int		status;

	cmd_path = find_command_path(cmd, env);
	if (!cmd_path)
		return (ft_putstr_fd(cmd, 2), ft_putstr_fd(ERR_CMD_NOT_FOUND, 2), 127);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), free(cmd_path), 1);
	if (pid == 0)
		execute_child_process(cmd_path, args, env);
	else
		status = wait_for_process(pid, cmd_path);
	return (status);
}

void	execute_commands(t_cmd *cmd, t_shell *shell, char *line)
{
	if (!cmd || !shell || !line)
		return ;
	if (!cmd->cmd && cmd->redirs)
	{
		handle_redirections(cmd);
		return ;
	}
	if (!cmd->next)
	{
		if (handle_redirections(cmd) < 0)
			return ;
		if (is_builtin_command(cmd->cmd))
			shell->exit_status = handle_builtin_commands(cmd, shell, line);
		else
			shell->exit_status = handle_external_command(cmd, shell);
	}
	else
		execute_piped_commands(cmd, shell);
}
