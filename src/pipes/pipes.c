/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:11:48 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/07 12:54:56 by mmarinov         ###   ########.fr       */
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

// Crear un pipe para conectar los procesos
// Redirigir la entrada
// Redirigir la salida
// Cerrar el file descriptor anterior
// Cerrar el pipe de lectura
// Cerrar el pipe de escritura
// Manejar redirecciones
// Ejecutar comando builtin
// Ejecutar comando externo
// Si no se ejecuta correctamente, salir con un error
// Cerrar el file descriptor anterior
// Cerrar la escritura en el pipe
// Guardar el file descriptor de lectura para el siguiente proceso
// Avanzar al siguiente comando
// Esperar a que todos los hijos terminen
// Esperar a todos los procesos hijos
// Guardar el estado de salida final
void	execute_piped_commands(t_cmd *cmd_list, t_shell *shell)
{
	int		pipefd[2];
	int		prev_fd;
	pid_t	pid;
	t_cmd	*curr;
	int		status;

	curr = cmd_list;
	prev_fd = -1;
	while (curr)
	{
		if (curr->next)
			pipe(pipefd);
		pid = fork();
		if (pid == 0)
		{
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
			handle_redirections(curr);
			if (is_builtin_command(curr->cmd))
				handle_builtin_commands(curr, shell, NULL);
			else
				execute_single_command(curr, shell->env);
			exit(EXIT_FAILURE);
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
	curr = cmd_list;
	while (curr)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		curr = curr->next;
	}
}
