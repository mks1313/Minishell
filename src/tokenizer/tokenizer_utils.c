/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:34:23 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/19 16:18:14 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_invalid_operator(char *str)
{
	return (
		(str[0] == '>' && str[1] == '>' && str[2] == '>') \
		|| (str[0] == '<' && str[1] == '<' && str[2] == '<') \
		|| (str[0] == '>' && str[1] == '<') \
		|| (str[0] == '<' && str[1] == '>') \
		|| (str[0] == '>' && str[1] == '|') \
		|| (str[0] == '<' && str[1] == '|'));
}

static bool	set_append_heredoc(char **str, t_tkn *token)
{
	if (**str == '>' && *(*str + 1) == '>')
	{
		token->type = TOK_APPEND;
		*str += 2;
		return (true);
	}
	if (**str == '<' && *(*str + 1) == '<')
	{
		token->type = TOK_HEREDOC;
		*str += 2;
		return (true);
	}
	return (false);
}

static bool	set_redir_pipe(char **str, t_tkn *token)
{
	if (**str == '>')
	{
		token->type = TOK_REDIR_OUT;
		(*str)++;
	}
	else if (**str == '<')
	{
		token->type = TOK_REDIR_IN;
		(*str)++;
	}
	else if (**str == '|')
	{
		token->type = TOK_PIPE;
		(*str)++;
	}
	else
		return (false);
	return (true);
}

static bool	set_operator_type(char **str, t_tkn *token)
{
	if (set_append_heredoc(str, token))
		return (true);
	return (set_redir_pipe(str, token));
}

t_tkn	*read_operator(char **str, t_shell *shell)
{
	t_tkn	*token;

	if (is_invalid_operator(*str))
	{
		syntax_error(shell, SYN_ERR_REDIRECT, 0);
		return (NULL);
	}
	token = ft_calloc(1, sizeof(t_tkn));
	if (!token)
		return (NULL);
	if (!set_operator_type(str, token))
	{
		free(token);
		return (NULL);
	}
	return (token);
}
