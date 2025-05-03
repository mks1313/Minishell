/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:09:54 by meghribe          #+#    #+#             */
/*   Updated: 2025/03/23 17:08:58 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)info;
	(void)context;
}

void	set_sig(struct sigaction *sa, void (*handler)(int, siginfo_t *, void *))
{
	sa->sa_flags = SA_SIGINFO;
	sa->sa_sigaction = handler;
	if (sigaction(SIGINT, sa, NULL) == -1)
		error_exit(ERR_SIG, EXIT_FAILURE);
}
