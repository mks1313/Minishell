/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:44:50 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/10 12:18:51 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_redirect(t_tkn_type type)
{
	return (type == TOK_REDIR_IN || type == TOK_REDIR_OUT
		|| type == TOK_APPEND || type == TOK_HEREDOC);
}

static void	add_cmd_to_list(t_cmd **cmd_list, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	if (!*cmd_list)
		*cmd_list = new_cmd;
	else
	{
		tmp = *cmd_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cmd;
	}
	// 🔍 Debug de punteros:
	LOG_DEBUG("🧱 CMD añadido a lista: %p\n", (void *)new_cmd);
	t_redir *rr = new_cmd->redirs;
	while (rr)
	{
		LOG_DEBUG("🔗 redir añadido: %p, delim=%s, fd=%d\n",
			(void *)rr, rr->delimiter, rr->fd);
		rr = rr->next;
	}
}

static void	start_new_cmd_if_needed(t_cmd **current_cmd)
{
	if (!*current_cmd)
		*current_cmd = create_cmd();
}

static void	process_token(t_cmd **current_cmd, t_tkn **tokens, t_cmd **cmd_list)
{
	if (is_redirect((*tokens)->type))
		handle_redirect(&(*current_cmd)->redirs, tokens);
	else if ((*tokens)->type == TOK_PIPE)
	{
		add_cmd_to_list(cmd_list, *current_cmd);
		*current_cmd = NULL;
		*tokens = (*tokens)->next;
	}
	else
	{
		add_arg_to_cmd(*current_cmd, (*tokens)->value);
		*tokens = (*tokens)->next;
	}
}

t_cmd	*parse_tokens(t_tkn *tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*current_cmd;

	cmd_list = NULL;
	current_cmd = NULL;
	while (tokens)
	{
		start_new_cmd_if_needed(&current_cmd);
		process_token(&current_cmd, &tokens, &cmd_list);
	}
	if (current_cmd)
		add_cmd_to_list(&cmd_list, current_cmd);
	return (cmd_list);
}
