/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:39:49 by meghribe          #+#    #+#             */
/*   Updated: 2025/05/21 20:12:49 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

/**
 * Processes a line of input, in both interactive and non-interactive modes.
 * Uses readline() for both, but only displays a prompt if interactive.
 */
static int	process_input_line(char **line_ptr, t_shell *shell, int interactive)
{
	char	*line;

	line = readline(interactive ? GREEN"minishell$ "RES : NULL);
	if (!line)
	{
		if (interactive)
			ft_putstr_fd("\nexit\n", 1);
		return (SHELL_EXIT);
	}
	*line_ptr = line;

	// Si el usuario pulsa Ctrl+C o Enter vacío
	if (interactive && line[0] == '\0')
	{
		shell->exit_status = g_exit_status;  // Preservar 130 si fue interrupción
		return (SHELL_CONTINUE);
	}

	if (interactive)
		add_history(line);

	// Ejecutar comandos (y modificar shell->exit_status)
	handle_commands(line, shell);

	// Solo si se ejecutó algo, actualiza g_exit_status
	g_exit_status = shell->exit_status;

	return (SHELL_CONTINUE);
}

/**
 * Shell main loop.
 * In non-interactive mode, executes only one line.
 */
static int	shell_loop(t_shell *shell, int interactive)
{
	char	*line;

	while (1)
	{
		if (process_input_line(&line, shell, interactive) == SHELL_EXIT)
			return (EXIT_SUCCESS);
		free(line);
		if (!interactive)
			break;
	}
	return (EXIT_SUCCESS);
}

/**
 * Main program entry point.
 * Initializes the shell and starts the loop.
 */
int	main(int argc, char *argv[], char **envp)
{
	t_shell	*shell;
	int		interactive;

	(void)argc;
	(void)argv;
	set_signals();
	interactive = isatty(STDIN_FILENO);
	if (init_shell(&shell))
		return (EXIT_FAILURE);
	if (setup_environment(shell, envp))
		return (clean_exit(shell, EXIT_FAILURE));
	return (clean_exit(shell, shell_loop(shell, interactive)));
}
