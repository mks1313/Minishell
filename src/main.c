/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:39:49 by meghribe          #+#    #+#             */
/*   Updated: 2025/05/20 22:26:33 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

static int	process_input_line(char **line_ptr, t_shell *shell, int inter)
{
	char	*line;

	if (inter)
		line = readline(GREEN"minishell$ "RES);
	else
		line = get_next_line(STDIN_FILENO);
	*line_ptr = line;
	if (!line)
	{
		if (inter)
			ft_putstr_fd("\nexit\n", 1);
		return (SHELL_EXIT);
	}
	if (*line && inter)
		add_history(line);
	handle_commands(line, shell);
	g_exit_status = shell->exit_status;
	return (SHELL_CONTINUE);
}

static int	shell_loop(t_shell *shell, int interactive)
{
	char	*line;

	while (1)
	{
		if (process_input_line(&line, shell, interactive) == SHELL_EXIT)
			return (EXIT_SUCCESS);
		free(line);
	}
	return (EXIT_SUCCESS);
}

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
