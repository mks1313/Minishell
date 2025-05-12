/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:39:58 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/12 16:51:11 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_cmd(void)
{
	return (ft_calloc(1, sizeof(t_cmd)));
}

char	*join_token_parts(t_tkn_part *parts)
{
	char	*tmp;
	char	*result;
	char	*joined;

	result = ft_strdup("");
	while (parts)
	{
		tmp = ft_strdup(parts->value);
		joined = ft_strjoin(result, tmp);
		free(result);
		free(tmp);
		result = joined;
		parts = parts->next;
	}
	return (result);
}

bool	handle_pipe(t_cmd **cmd_list, t_cmd **current_cmd, t_tkn **tokens)
{
	if (!*current_cmd || (!(*current_cmd)->cmd && !(*current_cmd)->redirs))
		return (ft_putstr_fd(SYN_ERR_PIPE, STDERR_FILENO), 0);
	add_cmd_to_list(cmd_list, *current_cmd);
	*current_cmd = NULL;
	*tokens = (*tokens)->next;
	return (true);
}

bool	handle_redirect_wrapper(t_cmd *cmd, t_tkn **tokens)
{
	t_redir	*redir;

	if (!(*tokens)->next)
		return (ft_putstr_fd(SYN_ERR_NL, STDERR_FILENO), 0);
	redir = create_redir(*tokens);
	if (!redir)
		return (false);
	add_redir_to_list(&cmd->redirs, redir);
	*tokens = (*tokens)->next;
	*tokens = (*tokens)->next;
	return (true);
}
