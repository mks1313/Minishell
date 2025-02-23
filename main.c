/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:39:49 by meghribe          #+#    #+#             */
/*   Updated: 2025/02/23 13:55:24 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
		write(fd, &s[i++], 1);
}

/*
static void	handle_signal(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)info;
	(void)context;
	ft_putstr_fd("DIE\n", 1);
	exit(EXIT_SUCCESS);
}

void	error_exit(const char *message, int exit_code)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd((char *)message, 2);
	ft_putstr_fd(RESET, 2);
	exit(exit_code);
}

void	set_sig(struct sigaction *sa, void (*handler)(int, siginfo_t *, void *))
{
	sa->sa_flags = SA_SIGINFO;
	sa->sa_sigaction = handler;
	if (sigaction(SIGINT, sa, NULL) == -1)
		error_exit(ERR_SIG, EXIT_FAILURE);

}
*/
int	main(int argc, char *argv[])
{
	char				*line;
	struct sigaction	sa;
	(void)argc;
	(void)argv;
	(void)sa;
//	set_sig(&sa, handle_signal);
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
	//	pause();
	}
	return (0);
}

