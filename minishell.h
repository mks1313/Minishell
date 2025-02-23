/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:47:17 by meghribe          #+#    #+#             */
/*   Updated: 2025/02/23 14:19:06 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
 * Libraries:
 * signal.h for sigaction()
 * readline for readline()
 * stdlib for exit()
 */
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

/* Colors */
# define RESET	"\033[0m"
# define RED	"\033[38;5;203m"
# define GOLD	"\033[38;5;220m"
# define GREEN	"\033[38;5;120m"

/* Errors */
# define ERR_SIG			"Error: sigaction.\n"
# define ERR_MEMORY			"Error: memory allocation failed.\n"

/* Functions */
void	ft_putstr_fd(char *s, int fd);
void	handle_signal(int sig, siginfo_t *info, void *context);
void	error_exit(const char *message, int exit_code);
void	set_sig(struct sigaction *sa, void (*handler)(int, siginfo_t *, void *));
#endif
