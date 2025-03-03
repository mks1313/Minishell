/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:47:17 by meghribe          #+#    #+#             */
/*   Updated: 2025/03/03 19:25:45 by mmarinov         ###   ########.fr       */
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
# include "../libft/includes/libft.h"

/* Colors */
# define RESET	"\033[0m"
# define RED	"\033[38;5;203m"
# define GOLD	"\033[38;5;220m"
# define GREEN	"\033[38;5;120m"

/* Errors */
# define EXIT_MSG			"exit\n"
# define ERR_SIG			"Error: sigaction.\n"
# define ERR_MEMORY			"Error: memory allocation failed.\n"

/* macros */
# define CD			"cd"
# define PWD		"pwd"
# define ENV		"env"
# define EXIT		"exit"
# define EXPORT 	"export"
# define UNSET		"unset"
/* Builtins */

/* Parsing flags */

/* ENV STRUCT*/
typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	t_env			*env;
	struct s_data	*next;
}	t_data;

/* Functions */
void	handle_signal(int sig, siginfo_t *info, void *context);
void	error_exit(const char *message, int exit_code);
typedef void	(*t_handler)(int, siginfo_t *, void *);
void	set_sig(struct sigaction *sa, t_handler handler);
#endif
