/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:44:50 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/10 16:03:17 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Checks if the token type is a redirection type.
 * Can be: TOK_REDIR_IN, TOK_REDIR_OUT, TOK_APPEND, TOK_HEREDOC
 */
static bool	is_redirect(t_tkn_type type)
{
	return (type >= TOK_REDIR_IN && type <= TOK_HEREDOC);
}

static void	start_new_cmd_if_needed(t_cmd **current_cmd)
{
	if (!*current_cmd)
		*current_cmd = create_cmd();
}

static bool	handle_pipe(t_cmd **cmd_list, t_cmd **current_cmd, t_tkn **tokens)
{
	if (!*current_cmd || (!(*current_cmd)->cmd && !(*current_cmd)->redirs))
		return (ft_putstr_fd(SYN_ERR_PIPE, 2), false);
	add_cmd_to_list(cmd_list, *current_cmd);
	*current_cmd = NULL;
	*tokens = (*tokens)->next;
	return (true);
}

static bool	handle_redirect_wrapper(t_cmd *cmd, t_tkn **tokens)
{
	if (!(*tokens)->next)
		return (ft_putstr_fd(SYN_ERR_NL, 2), false);
	handle_redirect(&cmd->redirs, tokens);
	return (true);
}

static bool	handle_word(t_cmd *cmd, t_tkn **tokens)
{
	add_arg_to_cmd(cmd, (*tokens)->value);
	*tokens = (*tokens)->next;
	return (true);
}

static bool	process_token_into_cmd(t_tkn **tokens, t_cmd **current_cmd, t_cmd **cmd_list)
{
	start_new_cmd_if_needed(current_cmd);
	if ((*tokens)->type == TOK_PIPE)
		return (handle_pipe(cmd_list, current_cmd, tokens));
	if (is_redirect((*tokens)->type))
		return (handle_redirect_wrapper(*current_cmd, tokens));
	return (handle_word(*current_cmd, tokens));
}

t_cmd	*parse_tokens(t_tkn *tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*current_cmd;
	t_tkn	*last_token;
	t_tkn	*empty_cmd;

	cmd_list = NULL;
	current_cmd = NULL;
	last_token = tokens;
	while (last_token && last_token->next)
		last_token = last_token->next;
	if (last_token && last_token->type == TOK_PIPE)
	{
		empty_cmd = create_token("", TOK_WORD);
		if (!empty_cmd)
			return (NULL);
		last_token->next = empty_cmd;
	}
	while (tokens)
	{
		if (!process_token_into_cmd(&tokens, &current_cmd, &cmd_list))
		{
			if (current_cmd)
				free_cmd_list(current_cmd);
			free_cmd_list(cmd_list);
			return (NULL);
		}
	}
	if (current_cmd)
		add_cmd_to_list(&cmd_list, current_cmd);
	return (cmd_list);
}
