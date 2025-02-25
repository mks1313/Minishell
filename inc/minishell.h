/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:30:54 by mmarinov          #+#    #+#             */
/*   Updated: 2025/02/23 13:46:57 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Toda la estrucutra de proyecto y las funciones

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <string.h>

# define SIDE_OUT	0
# define SIDE_IN	1

# define STDIN		0
# define STDOUT		1
# define STDER		2

# define TYPE_END	0
# define TYPE_PIPE	1
# define TYPE_BREAK	2

# ifndef TEST_SH
#  define TEST		1
# else
#  define TEST		0
# endif

typedef struct s_list
{
	char			**args;
	int				lengt;
	int				type;
	int				pipes[2];
	struct s_list	*previos;
	struct s_list	*next;
}				t_list;

int		show_error(char const *str);
int		exit_fatal(void);
void	exit_fatal_ptr(char const *str);
int		add_arg(t_list *cmd, char *arg);
#endif
