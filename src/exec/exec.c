/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:12:00 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/27 15:09:06 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	execute_commands(t_cmd *cmd, t_shell *shell, char *line)
{
	int	res;

	if (!cmd || !shell || !line)
		return ;
	if (!cmd->cmd && cmd->redirs)
	{
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
		return ;
	}
	if (!cmd->next)
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
	else
		execute_piped_commands(cmd, shell);
}
