/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:11:48 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/07 12:41:17 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	{
		perror("fork");
		return (1);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

void	execute_piped_commands(t_cmd *cmd_list, t_shell *shell)
{
	int		pipefd[2];	
	int		prev_fd = -1;
	pid_t	pid;
	t_cmd	*curr;
	int		status;

	curr = cmd_list;
	while (curr)
	{
		if (curr->next)
			pipe(pipefd);  // Crear un pipe para conectar los procesos
		pid = fork();
		if (pid == 0)
		{
			if (prev_fd != -1)
				dup2(prev_fd, STDIN_FILENO);  // Redirigir la entrada
			if (curr->next)
				dup2(pipefd[1], STDOUT_FILENO);  // Redirigir la salida
			if (prev_fd != -1)
				close(prev_fd);  // Cerrar el file descriptor anterior
			if (curr->next)
			{
				close(pipefd[0]);  // Cerrar el pipe de lectura
				close(pipefd[1]);  // Cerrar el pipe de escritura
			}
			handle_redirections(curr);  // Manejar redirecciones
			if (is_builtin_command(curr->cmd))
				handle_builtin_commands(curr, shell, NULL);  // Ejecutar comando builtin
			else
				execute_single_command(curr, shell->env);  // Ejecutar comando externo
			exit(EXIT_FAILURE);  // Si no se ejecuta correctamente, salir con un error
		}
		if (prev_fd != -1)
			close(prev_fd);  // Cerrar el file descriptor anterior
		if (curr->next)
		{
			close(pipefd[1]);  // Cerrar la escritura en el pipe
			prev_fd = pipefd[0];  // Guardar el file descriptor de lectura para el siguiente proceso
		}
		curr = curr->next;  // Avanzar al siguiente comando
	}
	// Esperar a que todos los hijos terminen
	curr = cmd_list;
	while (curr)
	{
		waitpid(-1, &status, 0);  // Esperar a todos los procesos hijos
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);  // Guardar el estado de salida final
		curr = curr->next;
	}
}
