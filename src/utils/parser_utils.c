/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:53:56 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/01 18:35:50 by mmarinov         ###   ########.fr       */
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

void	handle_exit_status(int *i, int l_e_s)
{
	ft_printf("%d", l_e_s);
	(*i)++;
}

void	handle_envp_count(int *i, t_env *env)
{
	ft_printf("%d", count_envp(env));
	(*i)++;
}

/*void	handle_pid(int *i)
{
	//ft_printf("%d", getpid());
	ft_printf("%d\n", get_pid_from_status());
	(*i)++;
}*/

void	process_input(const char *input, t_env *env, int l_e_s)
{
	single_quotes(input);
	double_quotes(input, env, l_e_s);
	expand_variable(input, env, l_e_s);
}
