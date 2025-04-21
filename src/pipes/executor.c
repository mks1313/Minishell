/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:11:24 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/21 13:32:24 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_single_command(t_cmd *cmd, t_env *env)
{
	(void)cmd;
	(void)env;
	return (0);
}

int	execute_cmds(t_cmd *cmds, t_env *env)
{
	t_pipe	pipe_data;

	if (!cmds)
		return (1);
	init_pipe_data(&pipe_data, cmds); // calcula cantidad de comandos
	if (pipe_data.n_cmds == 1)
		return (execute_single_command(cmds, env));
	return (execute_piped_commands(cmds, &pipe_data, env));
}
