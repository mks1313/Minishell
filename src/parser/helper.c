/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:35:52 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/24 16:59:42 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

char	*ft_strjoin_char(char *s, char c)
{
	char	*str;
	int		len;

	len = ft_strlen(s);
	str = malloc(len + 2);
	if (!str)
		return (NULL);
	ft_strcpy(str, s);
	str[len] = c;
	str[len + 1] = '\0';
	free(s);
	return (str);
}

//MIrara co lexer, para no duplicar
t_redir	*create_redir(t_tkn *tkn)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	if (tkn->type == TOK_REDIR_IN)
		redir->type = REDIR_IN;
	else if (tkn->type == TOK_REDIR_OUT)
		redir->type = REDIR_OUT;
	else if (tkn->type == TOK_APPEND)
		redir->type = REDIR_APPEND;
	else if (tkn->type == TOK_HEREDOC)
		redir->type = REDIR_HEREDOC;
	redir->file = ft_strdup(tkn->next->value);
	redir->fd = -1;
	redir->next = NULL;
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
}
