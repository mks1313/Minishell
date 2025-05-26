/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_parts.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:06:24 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/26 13:59:57 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Creates a new t_tkn_part node with the given text and quote type.
 * Allocates memory and initializes the structure.
 */
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

/*
 * Appends a t_tkn_part node to the end of a linked list of parts.
 * If the list is empty, it becomes the head.
 */
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

/*
 * Reads a quoted string from the input `str`, determines its quote type,
 * extracts the inner content, and creates a quoted t_tkn_part.
 * Returns NULL if the quote is not properly closed.
 */
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

/*
 * Reads the next fragment (part) of a token from the input `str`.
 * Handles quoted strings or plain unquoted words.
 * Special case: if `$` is followed by a quote, it reads as a quoted part.
 * Returns a t_tkn_part or NULL on error (e.g., unclosed quote).
 */
static t_tkn_part	*read_token_part(char **str)
{
	char		*start;
	char		*value;

	if (**str == '$' && (*(*str + 1) == '"' || *(*str + 1) == '\''))
	{
		(*str)++;
		return (read_quoted_part(str));
	}
	if (**str == '\'' || **str == '"')
		return (read_quoted_part(str));
	start = *str;
	while (**str && !ft_strchr(" \t\n|<>\"'", **str))
		(*str)++;
	value = ft_substr(start, 0, *str - start);
	return (create_part(value, Q_NONE));
}

/*
 * Builds a t_tkn token from the input string by reading multiple parts.
 * Each part is either quoted or unquoted. The loop stops at a shell delimiter.
 * If a part fails (e.g., bad quotes), it triggers a syntax error.
 * Returns a complete token with a list of parts and sets its type to TOK_WORD.
 */
t_tkn	*read_token(char **str, t_shell *shell)
{
	t_tkn_part	*parts;
	t_tkn_part	*part;
	t_tkn		*token;

	parts = NULL;
	token = ft_calloc(1, sizeof(t_tkn));
	if (!token)
		return (NULL);
	while (**str && !ft_strchr(" \t\n|<>", **str))
	{
		part = read_token_part(str);
		if (!part)
		{
			syntax_error(shell, SYN_ERR_UNCLOSED_QUOTE, 0);
			ft_free_parts(parts);
			free(token);
			return (NULL);
		}
		add_part(&parts, part);
	}
	token->type = TOK_WORD;
	token->parts = parts;
	return (token);
}
