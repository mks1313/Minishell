/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:09:54 by meghribe          #+#    #+#             */
/*   Updated: 2025/03/01 18:08:55 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "inc/minishell.h"

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)info;
	(void)context;
	/*
	ft_putstr_fd(GREEN "DIE\n" RESET, 1);
	exit(EXIT_SUCCESS);
	*/
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
