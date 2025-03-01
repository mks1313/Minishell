/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:39:49 by meghribe          #+#    #+#             */
/*   Updated: 2025/03/01 18:07:55 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char				*line;
	struct sigaction	sa;

	//ft_env(envp);
	(void)argc;
	(void)argv;
	(void)envp;
	set_sig(&sa, handle_signal);
	while (42)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			ft_putstr_fd("exit\n", 2);
			rl_clear_history();
			exit(EXIT_SUCCESS);
		}
		if (*line)
			add_history(line);
		free(line);
	}
	return (0);
}
