/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:12:00 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/06 18:25:56 by mmarinov         ###   ########.fr       */
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
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free(cmd_path);
		return (1);
	}
	if (pid == 0)
		execute_child_process(cmd_path, args, env);
	else
		status = wait_for_process(pid, cmd_path);
	return (status);
}

void	execute_commands(t_cmd *cmd, t_shell *shell, char *line)
{
	if (!cmd || !cmd->cmd || !shell || !line)
		return ;
	handle_heredoc(cmd, shell);
	if (!cmd->next)
	{
		if (is_builtin_command(cmd->cmd))
			shell->exit_status = handle_builtin_commands(cmd, shell, line);
		else
			shell->exit_status = handle_external_command(cmd, shell);
	}
	else
		execute_piped_commands(cmd, shell);
}
