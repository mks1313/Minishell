/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:09:54 by meghribe          #+#    #+#             */
/*   Updated: 2025/05/14 13:18:54 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Using a global variable to save the state of the last exit status */

/**
 * If the signal is SIGINT:
 * - Change the exeit_status to 130. 
 * - Writes a new line.
 * - Tells to the readline that we are in a new line.
 * - Removes the actual content of the prompt
 * - Displays again the prompt
 */
static void	handle_signal(int sig, siginfo_t *info, void *context)
{
	(void)info, (void)context;
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/**
 * Initializes the sigaction struct.
 * Configure the signals. 
 */
void	set_signals(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_signal;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		error_exit(ERR_SIG, EXIT_FAILURE);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * Restore the default behaviour of the signals.
 */
void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
