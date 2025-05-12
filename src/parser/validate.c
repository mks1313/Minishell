/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:00:00 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/12 16:15:39 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_command_syntax(t_cmd *cmd)
{
	if (!cmd)
		return (0);
	if (!cmd->cmd && cmd->redirs)
		return (1);
	if (!cmd->cmd && !cmd->redirs)
		return (0);
	if (cmd->cmd && cmd->cmd[0] == '\0')
		return (0);
	return (1);
}

static int	validate_pipes(t_cmd *cmd_list)
{
	t_cmd	*curr;

	curr = cmd_list;
	while (curr && curr->next)
	{
		if (!validate_command_syntax(curr))
			return (0);
		curr = curr->next;
	}
	if (curr && !validate_command_syntax(curr))
		return (0);
	if (curr && curr->next == NULL && !curr->cmd && !curr->redirs)
		return (0);
	return (1);
}

int	validate_syntax(t_cmd *cmd_list)
{
	t_cmd	*cmd;

	cmd = cmd_list;
	if (!cmd_list)
		return (1);
	if (cmd && !cmd->next && cmd->cmd && cmd->cmd[0] == '\0')
		return (ft_putstr_fd(SYN_ERR_NL, STDERR_FILENO), 0);
	if (!validate_pipes(cmd_list))
		return (ft_putstr_fd(SYN_ERR_PIPE, STDERR_FILENO), 0);
	return (1);
}
