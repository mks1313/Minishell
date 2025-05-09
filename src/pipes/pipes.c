/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:11:48 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/09 14:58:37 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Si execve falla, devuelve código 127
// Devuelve el código de salida del proceso hijo
// Si no terminó correctamente, devuelve 1
int	execute_single_command(t_cmd *cmd, t_env *env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (handle_redirections(cmd) < 0)
			exit(1);
		if (!cmd->args || !cmd->args[0])
			exit(0);
		exec_cmd(cmd->args[0], cmd->args, env);
		exit(127);
	}
	else if (pid < 0)
		return (perror("fork"), 1);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
/*
static void	child_process(t_cmd *curr, int prev_fd, int *pipefd, t_shell *shell)
{
	// 🐛 DEBUG: mostrar el comando actual (cmd y redir)
	printf("👶 child_process: cmd = %p\n", (void *)curr);

		if (!curr->redirs)
		printf(YELL"⚠️  cmd %p NO tiene redirs\n"RES, (void *)curr);
	else
	{
		t_redir *r = curr->redirs;
		while (r)
		{
			printf(CYAN"👶 redir en child: %p | type=%d | delim=%s | fd=%d\n"RES,
				(void *)r, r->type, r->delimiter, r->fd);
			r = r->next;
		}
	}
	// 🔁 duplicación estándar de stdin/stdout si hay pipes
	if (prev_fd != -1)
		dup2(prev_fd, STDIN_FILENO);
	if (curr->next)
		dup2(pipefd[1], STDOUT_FILENO);
	if (prev_fd != -1)
		close(prev_fd);
	if (curr->next)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	//if (curr->redirs && handle_redirections(curr) < 0)
	//	exit(1);
	// 🔧 aquí se aplican redirecciones (aquí explota si el redir es inválido)
	// 🧠 ejecutar comando builtin o externo
	if (is_builtin_command(curr->cmd))
		handle_builtin_commands(curr, shell, NULL);
	else
		execute_single_command(curr, shell->env);
	exit(EXIT_FAILURE);
}*/

static void	child_process(t_cmd *curr, int prev_fd, int *pipefd, t_shell *shell)
{
	// Heredoc/redirecciones primero
	if (curr->redirs && handle_redirections(curr) < 0)
		exit(1);
	// Redirigir STDIN desde el pipe anterior
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	// Redirigir STDOUT al pipe siguiente
	if (curr->next)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	}
	// Ejecutar comando
	if (is_builtin_command(curr->cmd))
		handle_builtin_commands(curr, shell, NULL);
	else
		execute_single_command(curr, shell->env);
	exit(EXIT_FAILURE); // Solo si falló algo
}

static void	wait_for_children(t_cmd *cmd_list, t_shell *shell)
{
	int		status;
	t_cmd	*curr;

	curr = cmd_list;
	while (curr)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		curr = curr->next;
	}
}

void	execute_piped_commands(t_cmd *cmd_list, t_shell *shell)
{
	int		pipefd[2];
	int		prev_fd;
	pid_t	pid;
	t_cmd	*curr;

	curr = cmd_list;
	prev_fd = -1;
	while (curr)
	{
		if (curr->next && pipe(pipefd) == -1)
		{
			perror("pipe");
			return;
		}
		pid = fork();
		if (pid == 0)
			child_process(curr, prev_fd, pipefd, shell);
		else if (pid < 0)
		{
			perror("fork");
			return;
		}
		if (prev_fd != -1)
			close(prev_fd);
		if (curr->next)
		{
			close(pipefd[1]);
			prev_fd = pipefd[0];
		}
		curr = curr->next;
	}
	wait_for_children(cmd_list, shell);
}
