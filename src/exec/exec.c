/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:12:00 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/28 13:14:45 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Waits for the child process to finish and returns its final exit status.
 * If it exited normally, returns WEXITSTATUS. If terminated by signal,
 * returns 128 + signal number.
**/
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

/**
 * Replaces the current process image with the given command using execve.
 * If execve fails, prints an error and exits with failure.
 **/
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

/**
 * Creates a child process and executes the given command.
 * Parent waits and returns exit status; child replaces itself with execve.
**/
static int	launch_child(char *cmd_path, char **args, t_env *env)
{
	pid_t	pid;
	int		status;

	status = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), free(cmd_path), 1);
	if (pid == 0)
		execute_child_process(cmd_path, args, env);
	else
		status = wait_for_process(pid, cmd_path);
	set_signals();
	return (status);
}

/**
 * Executes a command by resolving its path, validating it, and running it.
 * Handles edge cases like "." or "..", returns appropriate exit code.
**/
int	exec_cmd(char *cmd, char **args, t_env *env)
{
	char	*cmd_path;
	int		res;

	res = check_dot_dot_cmd(cmd);
	if (res != 0)
		return (res);
	cmd_path = check_cmd_path(cmd, env);
	if (!cmd_path)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(ERR_CMD_NOT_FOUND, STDERR_FILENO);
		return (127);
	}
	res = validate_cmd(cmd_path);
	if (res != 0)
	{
		free(cmd_path);
		return (res);
	}
	return (launch_child(cmd_path, args, env));
}

/**
 * Executes the full command including redirections and builtins.
 * Delegates redir-only, single or piped commands accordingly.
 */
void	execute_commands(t_cmd *cmd, t_shell *shell, char *line)
{
	if (!cmd || !shell || !line)
		return ;
	if (!cmd->cmd && cmd->redirs)
	{
		handle_redir_only_command(cmd, shell);
		return ;
	}
	if (!cmd->next)
		execute_single_command(cmd, shell, line);
	else
		execute_piped_commands(cmd, shell);
}
