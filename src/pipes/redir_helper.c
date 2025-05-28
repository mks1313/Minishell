/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:35:52 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/28 20:56:51 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Sets the redirection type based on the token type.
 */
static void	set_redir_type(t_redir *redir, t_tkn *tkn)
{
	if (tkn->type == TOK_REDIR_IN)
		redir->type = REDIR_IN;
	else if (tkn->type == TOK_REDIR_OUT)
		redir->type = REDIR_OUT;
	else if (tkn->type == TOK_APPEND)
		redir->type = REDIR_APPEND;
	else if (tkn->type == TOK_HEREDOC)
		redir->type = REDIR_HEREDOC;
}

/**
 * Sets the file or delimiter for the redirection based on the token.
 */
static void	set_redir_target(t_redir *redir, t_tkn *tkn)
{
	char	*joined;

	joined = join_token_parts(tkn->parts);
	if (redir->type == REDIR_HEREDOC)
	{
		redir->delimiter = joined;
		redir->file = NULL;
	}
	else
	{
		redir->file = joined;
		redir->delimiter = NULL;
	}
}

/**
 * Creates a new redirection object based on the token.
 */
t_redir	*create_redir(t_tkn *tkn)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	set_redir_type(redir, tkn);
	set_redir_target(redir, tkn->next);
	if (redir->type == REDIR_HEREDOC && tkn->next && tkn->next->parts)
		redir->delim_quote = tkn->next->parts->quote;
	else
		redir->delim_quote = Q_NONE;
	redir->fd = -1;
	return (redir);
}

/**
 * Adds a redirection to the redirection list.
 */
void	add_redir_to_list(t_redir **list, t_redir *new_redir)
{
	t_redir	*tmp;

	if (!*list)
		*list = new_redir;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_redir;
	}
}

/**
 * Handles a redirection token and adds it to the redirection list.
 */
void	handle_redirect(t_redir **redir_list, t_tkn **tkn)
{
	t_redir	*redir;

	redir = create_redir(*tkn);
	if (!redir)
		return ;
	add_redir_to_list(redir_list, redir);
	*tkn = (*tkn)->next;
	if (*tkn)
		*tkn = (*tkn)->next;
}
