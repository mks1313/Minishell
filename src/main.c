/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:39:49 by meghribe          #+#    #+#             */
/*   Updated: 2025/05/08 20:15:25 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

static int	process_input_line(char **line_ptr, t_shell *shell)
{
	char	*line;

	line = readline(GREEN"minishell$ "RES);
	*line_ptr = line;
	if (!line)
		return (ft_putstr_fd("\nexit\n", 1), SHELL_EXIT);
	if (*line)
	{
		add_history(line);
		handle_commands(line, shell);
	}
	return (SHELL_CONTINUE);
}

static int	shell_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		if (process_input_line(&line, shell) == SHELL_EXIT)
			return (EXIT_SUCCESS);
		free(line);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[], char **envp)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	set_signals();
	if (init_shell(&shell))
		return (EXIT_FAILURE);
	if (setup_environment(shell, envp))
		return (clean_exit(shell, EXIT_FAILURE));
	return (clean_exit(shell, shell_loop(shell)));
}
