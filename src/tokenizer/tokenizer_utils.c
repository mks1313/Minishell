/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:34:23 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/14 14:00:45 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tkn_part	*create_part(char *text, t_tkn_quote quote)
{
	t_tkn_part	*part;

	part = ft_calloc(1, sizeof(t_tkn_part));
	if (!part)
		return (NULL);
	part->value = text;
	part->quote = quote;
	return (part);
}

static void	add_part(t_tkn_part **head, t_tkn_part *new)
{
	t_tkn_part	*curr;

	curr = *head;
	if (!curr)
		*head = new;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

static t_tkn_part	*read_quoted_part(char **str)
{
	t_tkn_quote	quote;
	char		*start;
	char		*value;
	char		quote_char;

	if (**str == '\'')
		quote = Q_SINGLE;
	else
		quote = Q_DOUBLE;
	quote_char = *(*str)++;
	start = *str;
	while (**str && **str != quote_char)
		(*str)++;
	if (**str != quote_char)
		return (NULL);
	value = ft_substr(start, 0, *str - start);
	(*str)++;
	return (create_part(value, quote));
}

static t_tkn_part	*read_token_part(char **str)
{
	char		*start;
	char		*value;

	if (**str == '\'' || **str == '"')
		return (read_quoted_part(str));
	start = *str;
	while (**str && !ft_strchr(" \t\n|<>\"'", **str))
		(*str)++;
	value = ft_substr(start, 0, *str - start);
	return (create_part(value, Q_NONE));
}

t_tkn	*read_token(char **str)
{
	t_tkn_part	*parts;
	t_tkn		*token;
	t_tkn_part	*part;

	parts = NULL;
	token = ft_calloc(1, sizeof(t_tkn));
	while (**str && !ft_strchr(" \t\n|<>", **str))
	{
		part = read_token_part(str);
		if (!part)
		{
			ft_putstr_fd(SYN_ERR_UNCLOSED_QUOTE, STDERR_FILENO);
    		free(token);
			return (NULL);
		}
		add_part(&parts, part);
	}
	token->type = TOK_WORD;
	token->parts = parts;
	return (token);
}

static bool	is_invalid_operator(char *str)
{
	return ((str[0] == '>' && str[1] == '>' && str[2] == '>') ||
		(str[0] == '<' && str[1] == '<' && str[2] == '<') ||
		(str[0] == '>' && str[1] == '<') ||
		(str[0] == '<' && str[1] == '>') ||
		(str[0] == '>' && str[1] == '|') ||
		(str[0] == '<' && str[1] == '|'));
}

static bool	set_operator_type(char **str, t_tkn *token)
{
	if (**str == '>' && *(*str + 1) == '>')
	{
		token->type = TOK_APPEND;
		*str += 2;
	}
	else if (**str == '<' && *(*str + 1) == '<')
	{
		token->type = TOK_HEREDOC;
		*str += 2;
	}
	else if (**str == '>')
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

t_tkn	*read_operator(char **str)
{
	t_tkn	*token;

	if (is_invalid_operator(*str))
	{
		ft_putstr_fd(SYN_ERR_REDIRECT, STDERR_FILENO);
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
