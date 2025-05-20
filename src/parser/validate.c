/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:00:00 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/20 17:45:26 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_syntax(t_cmd *cmd_list, t_shell *shell)
{
	t_cmd	*cmd;

	cmd = cmd_list;
	if (!cmd_list)
		return (1);
	if (!cmd->cmd && !cmd->redirs)
		return (syntax_error(shell, SYN_ERR_EMPTY, 0));
	if (cmd && !cmd->next && cmd->cmd && cmd->cmd[0] == '\0')
		return (syntax_error(shell, SYN_ERR_NL, 0));
	return (1);
}
