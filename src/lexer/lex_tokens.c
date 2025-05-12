/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:38:06 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/10 13:33:12 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lex_tokens(t_tkn *tkn)
{
	while (tkn)
	{
		if (tkn->type != TOK_OPERATOR)
		{
			tkn = tkn->next;
			continue;
		}
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
		else
			tkn->type = TOK_WORD;
		tkn = tkn->next;
	}
}
