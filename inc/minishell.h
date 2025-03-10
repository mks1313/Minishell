/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:47:17 by meghribe          #+#    #+#             */
/*   Updated: 2025/03/10 15:15:03 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "sys_includes.h"
# include "shell_types.h"
# include "functions.h"

/* Colors */
# define RES	"\033[0m"
# define RED	"\033[1;31m"
# define GOLD	"\033[38;5;220m"
# define GREEN	"\033[38;5;120m"
# define YELL	"\033[1;33m"
# define LGREY	"\033[38;5;250m"
# define BLUE	"\033[1;34m"
# define CYAN	"\033[1;36m"
# define MAG	"\033[1;35m"

/* Errors */
# define EXIT_MSG			"exit\n"
# define ERR_SIG			"Error: sigaction.\n"
# define ERR_MEMORY			"Error: memory allocation failed.\n"
# define EXIT_SUCCESS_CODE 0
# define EXIT_TOO_MANY_ARGS 1
# define EXIT_NON_NUMERIC_ARG 2

/* macros, comandos y builtins */
# define CD			"cd"
# define PWD		"pwd"
# define ENV		"env"
# define EXIT		"exit"
# define EXPORT 	"export"
# define UNSET		"unset"
# define ECHO		"echo"

#endif
