/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:47:17 by meghribe          #+#    #+#             */
/*   Updated: 2025/05/12 12:51:08 by mmarinov         ###   ########.fr       */
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
# include "messages.h"

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

/* macros, comandos y builtins */
# define CD			"cd"
# define PWD		"pwd"
# define ENV		"env"
# define EXIT		"exit"
# define EXPORT 	"export"
# define UNSET		"unset"
# define ECHO		"echo"

#endif
