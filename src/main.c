/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:15:42 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/26 17:38:55 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

/*
 * Reads a line in interactive mode using readline().
 * Handles Ctrl+D (EOF) and adds input to history.
 * Returns:
 *   SHELL_CONTINUE on success,
 *   SHELL_EXIT on EOF (Ctrl+D).
 */
static int	read_interactive_line(char **line_ptr)
{
	char	*line;

	line = readline(GREEN"minishell$ "RES);
	if (!line)
		return (ft_putstr_fd("\nexit\n", 1), SHELL_EXIT);
	if (line[0] == '\0')
	{
		*line_ptr = line;
		return (SHELL_CONTINUE);
	}
	add_history(line);
	*line_ptr = line;
	return (SHELL_CONTINUE);
}

/*
 * Reads a line in non-interactive mode from STDIN using read().
 * Stops at newline, EOF, or buffer limit.
 * Returns:
 *   SHELL_CONTINUE on success,
 *   SHELL_EXIT on EOF or read error.
 */
static int	read_noninteractive_line(char **line_ptr)
{
	char	buffer[4096];
	ssize_t	bytes_read;
	int		i;

	i = 0;
	while (i < 4095)
	{
		bytes_read = read(STDIN_FILENO, &buffer[i], 1);
		if (bytes_read <= 0 || buffer[i] == '\n')
			break ;
		i++;
	}
	if (bytes_read <= 0 && i == 0)
		return (SHELL_EXIT);
	buffer[i] = '\0';
	*line_ptr = ft_strdup(buffer);
	if (!*line_ptr)
		return (SHELL_EXIT);
	return (SHELL_CONTINUE);
}

/*
 * Processes a line of input depending on shell mode.
 * Reads a line via readline() or read(), then executes it.
 * Updates global exit status.
 * Returns:
 *  SHELL_CONTINUE to continue the loop,
 *  SHELL_EXIT to exit the shell.
 */
static int	process_input_line(char **line_ptr, t_shell *shell, int interactive)
{
	int	status;

	if (interactive)
		status = read_interactive_line(line_ptr);
	else
		status = read_noninteractive_line(line_ptr);
	if (status != SHELL_CONTINUE)
		return (status);
	handle_commands(*line_ptr, shell);
	g_exit_status = shell->exit_status;
	return (SHELL_CONTINUE);
}

/*
 * Main shell loop.
 * Keeps reading and processing lines.
 * In non-interactive mode, processes only one line and exits.
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
			break ;
	}
	return (EXIT_SUCCESS);
}

/*
 * Entry point of the Minishell.
 * Initializes shell, environment, signals and starts the main loop.
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
