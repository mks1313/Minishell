/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:39:49 by meghribe          #+#    #+#             */
/*   Updated: 2025/05/24 15:43:04 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

/**
 * Processes a line of input, in both interactive and non-interactive modes.
 * Uses readline() for interactive mode and read() for non-interactive mode.
 */
static int	process_input_line(char **line_ptr, t_shell *shell, int interactive)
{
	char	*line;
	char	buffer[4096];
	ssize_t	bytes_read;
	int		i;

	if (interactive)
	{
		line = readline(GREEN"minishell$ "RES);
		if (!line)
			return (ft_putstr_fd("\nexit\n", 1), SHELL_EXIT);
		if (line[0] == '\0')
		{
			*line_ptr = line;
			return (SHELL_CONTINUE);
		}
		add_history(line);
	}
	else
	{
		i = 0;
		while ((bytes_read = read(STDIN_FILENO, &buffer[i], 1)) > 0 && buffer[i] != '\n' && i < 4095)
			i++;
		if (bytes_read <= 0 && i == 0)
			return (SHELL_EXIT);
		buffer[i] = '\0';
		line = ft_strdup(buffer);
		if (!line)
			return (SHELL_EXIT);
	}
	*line_ptr = line;
	handle_commands(line, shell);
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

