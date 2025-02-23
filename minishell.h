/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:47:17 by meghribe          #+#    #+#             */
/*   Updated: 2025/02/23 13:18:13 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h> // for sigaction
# include <unistd.h>
# include <stdlib.h> // for exit
#include <readline/readline.h>
#include <readline/history.h>

# define RESET	"\033[0m"
# define RED	"\033[38;5;203m"
# define GOLD	"\033[38;5;220m"
# define GREEN	"\033[38;5;120m"

# define ERR_SIG			"Error: sigaction.\n"
# define ERR_MEMORY			"Error: memory allocation failed.\n"
#endif
