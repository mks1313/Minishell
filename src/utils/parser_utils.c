/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:53:56 by mmarinov          #+#    #+#             */
/*   Updated: 2025/03/30 16:12:25 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_envp(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

void	handle_exit_status(int *i, int last_exit_status)
{
	ft_printf("%d", last_exit_status);
	(*i)++;
}

void	handle_envp_count(int *i, t_env *env)
{
	ft_printf("%d", count_envp(env));
	(*i)++;
}

void	handle_pid(int *i)
{
	ft_printf("%d", getpid());
	(*i)++;
}

void	process_input(const char *input, t_env *env, int last_exit_status)
{
    handle_single_quotes(input);
    handle_double_quotes(input, env);
    expand_variable(input, env, last_exit_status);
}
