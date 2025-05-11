/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:35:52 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/08 19:35:21 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	set_redir_target(t_redir *redir, t_tkn *tkn)
{
	if (redir->type == REDIR_HEREDOC)
	{
		redir->delimiter = ft_strdup(tkn->next->value);
		redir->file = NULL;
	}
	else
	{
		redir->file = ft_strdup(tkn->next->value);
		redir->delimiter = NULL;
	}
}

t_redir	*create_redir(t_tkn *tkn)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	set_redir_type(redir, tkn);
	set_redir_target(redir, tkn);
	redir->fd = -1;
	return (redir);
}

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

void	handle_redirect(t_redir **redir_list, t_tkn **tkn)
{
	t_redir	*redir;

	if (!*tkn || !(*tkn)->next)
		return ;
	redir = create_redir(*tkn);
	if (!redir)
		return ;
	add_redir_to_list(redir_list, redir);
	*tkn = (*tkn)->next;
	if (*tkn)
		*tkn = (*tkn)->next;
}
