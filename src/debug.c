/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:59:15 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/21 13:18:04 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*redir_type_str(t_redir_type type)
{
	if (type == REDIR_IN)
		return ("<");
	else if (type == REDIR_OUT)
		return (">");
	else if (type == REDIR_APPEND)
		return (">>");
	else if (type == REDIR_HEREDOC)
		return ("<<");
	return ("(unknown)");
}

void	print_cmd_list(t_cmd *cmd)
{
	int		i;
	t_redir	*redir;

	i = 0;
	while (cmd)
	{
		printf("========== CMD #%d ==========\n", i);
		printf("Command   : %s\n", cmd->cmd ? cmd->cmd : "(null)");
		printf("Args      : ");
		if (cmd->args)
		{
			int j = 0;
			while (cmd->args[j])
			{
				printf("[%s] ", cmd->args[j]);
				j++;
			}
			printf("\n");
		}
		else
			printf("(none)\n");

		printf("Redirs    :\n");
		redir = cmd->redirs;
		while (redir)
		{
			printf("  %s %s\n", redir_type_str(redir->type),
				redir->file ? redir->file : "(null)");
			redir = redir->next;
		}
		cmd = cmd->next;
		i++;
	}
}

