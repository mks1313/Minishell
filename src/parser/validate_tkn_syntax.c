/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tkn_syntax.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:15:25 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/13 15:23:27 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*get_token_name(t_tkn_type type)
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
	return ("`newline'");
}

static void	print_token_syntax_error(t_tkn_type type)
{
	const char	*token;

	token = get_token_name(type);
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	ft_putstr_fd((char *)token, 2);
	ft_putstr_fd("\n", 2);
}

static bool	validate_pipe(t_tkn *prev, t_tkn *curr)
{
	if (!prev || !curr->next || curr->next->type == TOK_PIPE)
	{
		ft_putstr_fd(SYN_ERR_PIPE, 2);
		return (false);
	}
	return (true);
}

static bool	validate_redirect(t_tkn *token)
{
	t_tkn	*next;

	next = token->next;
	if (!next)
	{
		print_token_syntax_error(TOK_EOF);
		return (false);
	}
	if (next->type != TOK_WORD)
	{
		print_token_syntax_error(next->type);
		return (false);
	}
	if (next->next &&
		(next->next->type >= TOK_REDIR_IN &&
		 next->next->type <= TOK_HEREDOC))
	{
		print_token_syntax_error(next->next->type);
		return (false);
	}
	return (true);
}

bool	validate_token_syntax(t_tkn *tokens)
{
	t_tkn	*prev;

	prev = NULL;
	while (tokens)
	{
		if (tokens->type == TOK_PIPE)
		{
			if (!validate_pipe(prev, tokens))
				return (false);
		}
		else if (tokens->type >= TOK_REDIR_IN &&
			tokens->type <= TOK_HEREDOC)
		{
			if (!validate_redirect(tokens))
				return (false);
		}
		else if (tokens->type == TOK_OPERATOR)
		{
			ft_putstr_fd(SYN_ERR_INVALID_OPERATOR, 2);
			return (false);
		}
		prev = tokens;
		tokens = tokens->next;
	}
	return (true);
}
