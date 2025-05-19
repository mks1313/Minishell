/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:00:00 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/19 15:15:19 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_syntax(t_cmd *cmd_list)
{
	t_cmd	*cmd;

	cmd = cmd_list;
	if (!cmd_list)
		return (1);
	if (!cmd->cmd && cmd->redirs)
		return (0);
	if (cmd && !cmd->next && cmd->cmd && cmd->cmd[0] == '\0')
		return (ft_putstr_fd(SYN_ERR_NL, STDERR_FILENO), 0);
	return (1);
}
