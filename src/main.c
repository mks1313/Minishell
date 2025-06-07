/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:39:49 by meghribe          #+#    #+#             */
/*   Updated: 2025/05/28 21:13:51 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

/**
 * Processes a line of input in interactive mode.
 * Reads the line using readline(), returns control to shell loop.
 */
static int	process_interactive_input(char **line_ptr)
{
	*line_ptr = readline(GREEN"minishell$ "RES);
	if (!*line_ptr)
		return (ft_putstr_fd("\nexit\n", 1), SHELL_EXIT);
	if (**line_ptr == '\0')
	{
		free(*line_ptr);
		return (SHELL_CONTINUE);
	}
	add_history(*line_ptr);
	return (SHELL_CONTINUE);
}

/**
 * Processes a line of input in non-interactive mode.
 * Reads a single line using read(), returns control to shell loop.
 */
static int	process_non_interactive_input(char **line_ptr)
{
	char	buffer[4096];
	ssize_t	bytes_read;
	int		i;

	i = 0;
	bytes_read = read(STDIN_FILENO, &buffer[i], 1);
	while (bytes_read > 0 && buffer[i] != '\n' && i < 4095)
	{
		i++;
		bytes_read = read(STDIN_FILENO, &buffer[i], 1);
	}
	if (bytes_read <= 0 && i == 0)
		return (SHELL_EXIT);
	buffer[i] = '\0';
	*line_ptr = ft_strdup(buffer);
	if (!*line_ptr)
		return (SHELL_EXIT);
	return (SHELL_CONTINUE);
}

/**
 * Process a line of input depending on the mode
 * (interactive or non-interactive).
 * Calls the appropriate input processing function based on the mode.
 */
static int	process_input_line(char **line_ptr, int interactive)
{
	if (interactive)
		return (process_interactive_input(line_ptr));
	return (process_non_interactive_input(line_ptr));
}

/**
 * Shell main loop. In non-interactive mode, executes one line.
 * In interactive mode, enters a loop reading commands.
 */
static int	shell_loop(t_shell *shell, int interactive)
{
	char	*line;
	int		ret_val;

	while (1)
	{
		ret_val = process_input_line(&line, interactive);
		if (ret_val == SHELL_EXIT)
			return (EXIT_SUCCESS);
		handle_commands(line, shell);
		g_exit_status = shell->exit_status;
		free(line);
		if (!interactive)
			break ;
	}
	return (EXIT_SUCCESS);
}

/**
 * Main entry point. Initializes the shell and starts the shell loop.
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
