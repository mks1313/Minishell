/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tkn_syntax.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:15:25 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/20 19:20:01 by mmarinov         ###   ########.fr       */
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

char	*get_token_name(t_tkn_type type)
{
	if (type == TOK_PIPE)
		return ("`|'");
	if (type == TOK_REDIR_IN)
		return ("`<'");
	if (type == TOK_REDIR_OUT)
		return ("`>'");
	if (type == TOK_APPEND)
		return ("`>>'");
	if (type == TOK_HEREDOC)
		return ("`<<'");
	if (type == TOK_OPERATOR)
		return ("`invalid operator'");
	return ("`newline'");
}

static bool	validate_pipe(t_tkn *prev, t_tkn *curr, t_shell *shell)
{
	if (!prev || !curr->next || curr->next->type == TOK_PIPE)
		return (syntax_error(shell, NULL, TOK_PIPE));
	return (true);
}

static bool	validate_redirect(t_tkn *token, t_shell *shell)
{
	t_tkn	*next;

	next = token->next;
	if (!next)
		return (syntax_error(shell, NULL, TOK_EOF));
	if (next->type != TOK_WORD)
		return (syntax_error(shell, NULL, next->type));
	return (true);
}

bool	validate_token_syntax(t_tkn *tokens, t_shell *shell)
{
	t_tkn	*prev;

	prev = NULL;
	while (tokens)
	{
		if (tokens->type == TOK_PIPE)
		{
			if (!validate_pipe(prev, tokens, shell))
				return (false);
		}
		else if (tokens->type >= TOK_REDIR_IN && tokens->type <= TOK_HEREDOC)
		{
			if (!validate_redirect(tokens, shell))
				return (false);
		}
		else if (tokens->type == TOK_OPERATOR)
		{
			return (syntax_error(shell, NULL, TOK_OPERATOR));
		}
		prev = tokens;
		tokens = tokens->next;
	}
	return (true);
}
