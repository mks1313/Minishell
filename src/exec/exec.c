/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:12:00 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/19 11:52:52 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_directory(const char *path)
{
	struct stat	info;

	if (stat(path, &info) != 0)
	{
		perror("stat failed");
		return (-1);
	}
	if (S_ISDIR(info.st_mode))
		return (1);
	return (0);
}

static int	wait_for_process(pid_t pid, char *cmd_path)
{
	int	status;
	int	exit_code;
	int	sig;

	waitpid(pid, &status, 0);
	free(cmd_path);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
		exit_code = 128 + sig;
	}
	else
		exit_code = 1;
	return (exit_code);
}

static int	execute_child_process(char *cmd_path, char **args, t_env *env)
{
	char	**envp;

	reset_signals();
	envp = env_to_array(env);
	if (execve(cmd_path, args, envp) == -1)
		perror(cmd_path);
	clean_array(envp);
	free(cmd_path);
	exit(EXIT_FAILURE);
}

int	exec_cmd(char *cmd, char **args, t_env *env)
{
    char	*cmd_path;
    pid_t	pid;
    int		status;

    status = 0;
    if (ft_strchr(cmd, '/'))
        cmd_path = ft_strdup(cmd);
    else
        cmd_path = find_command_path(cmd, env);
    if (!cmd_path)
        return (ft_putstr_fd(cmd, 2), ft_putstr_fd(ERR_CMD_NOT_FOUND, 2), 127);
    int res = is_directory(cmd_path);
    if (res == 1)
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        ft_putstr_fd(cmd_path, STDERR_FILENO);
        ft_putendl_fd(": is a directory", STDERR_FILENO);
        free(cmd_path);
        return (126);
    }
    else if (res == -1)
    {
        perror("minishell");
        free(cmd_path);
        return (127);
    }
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    pid = fork();
	if (pid < 0)
		return (perror("fork"), free(cmd_path), 1);
	if (pid == 0)
	{
		reset_signals();
		execute_child_process(cmd_path, args, env);
	}
	else
	{
		status = wait_for_process(pid, cmd_path);
	}
	set_signals();
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
