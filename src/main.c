/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:39:49 by meghribe          #+#    #+#             */
/*   Updated: 2025/05/21 21:55:21 by mmarinov         ###   ########.fr       */
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

	//line = readline(interactive ? GREEN"minishell$ "RES : NULL);
	line = interactive ? readline(GREEN"minishell$ "RES) : readline(NULL);
	if (!line)
	{
		if (interactive)
			ft_putstr_fd("\nexit\n", 1);
		return (SHELL_EXIT);
	}
	*line_ptr = line;
	LOG_DEBUG("Read line: [%s]\n", line ? line : "NULL");
	LOG_DEBUG("Read line: [%s]", line ? line : "NULL");
	if (interactive && line[0] == '\0')
	{
		LOG_DEBUG("Empty line (possibly Ctrl+C), preserving g_exit_status = %d\n", g_exit_status);
		shell->exit_status = g_exit_status;
		return (SHELL_CONTINUE);
	}
	if (interactive)
		add_history(line);
	handle_commands(line, shell);
	LOG_DEBUG("After handle_commands, shell->exit_status = %d\n", shell->exit_status);
	g_exit_status = shell->exit_status;
	LOG_DEBUG("g_exit_status updated to: %d\n", g_exit_status);
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
