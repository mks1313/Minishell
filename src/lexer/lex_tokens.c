/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:38:06 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/21 12:40:57 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_tkn_operator(const char *s)
{
	return (ft_strcmp(s, "|") == 0
		|| ft_strcmp(s, "<") == 0
		|| ft_strcmp(s, ">") == 0
		|| ft_strcmp(s, "<<") == 0
		|| ft_strcmp(s, ">>") == 0
	);
}

void	lex_tokens(t_tkn *tkn)
{
	while (tkn)
	{
		if (ft_strcmp(tkn->value, "|") == 0)
			tkn->type = TOK_PIPE;
		else if (ft_strcmp(tkn->value, ">") == 0)
			tkn->type = TOK_REDIR_OUT;
		else if (ft_strcmp(tkn->value, "<") == 0)
			tkn->type = TOK_REDIR_IN;
		else if (ft_strcmp(tkn->value, ">>") == 0)
			tkn->type = TOK_APPEND;
		else if (ft_strcmp(tkn->value, "<<") == 0)
			tkn->type = TOK_HEREDOC;
		else if (is_tkn_operator(tkn->value))
			tkn->type = TOK_OPERATOR;
		else
			tkn->type = TOK_WORD;
		tkn = tkn->next;
	}
}
