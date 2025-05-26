/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:34:23 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/26 14:11:23 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Checks for invalid operator sequences such as:
 * - Too many redirection characters (e.g., >>>, <<<)
 * - Mismatched combinations (e.g., ><, <>)
 * - Redirection followed by a pipe (e.g., >|, <|)
 *
 * Returns true if the operator is invalid, false otherwise.
 */
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

/*
 * Checks if the input starts with an append (>>) or heredoc (<<) operator.
 * If so, sets the token type accordingly and advances the string pointer.
 *
 * Returns true if an operator was matched and set, false otherwise.
 */
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

/*
 * Checks if the input starts with a single redirection or pipe:
 * - > (redirect out)
 * - < (redirect in)
 * - | (pipe)
 * Sets the token type and advances the pointer accordingly.
 *
 * Returns true if a valid operator was found, false otherwise.
 */
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

/*
 * Tries to classify the current operator in the input as:
 * - Append (>>)
 * - Heredoc (<<)
 * - Redirect in/out or Pipe
 *
 * Returns true if a valid operator was found and set, false otherwise.
 */
static bool	set_operator_type(char **str, t_tkn *token)
{
	if (set_append_heredoc(str, token))
		return (true);
	return (set_redir_pipe(str, token));
}

/*
 * Main function to read an operator token from input.
 * - Validates the operator syntax.
 * - Allocates and returns a t_tkn with the correct type set.
 * - On syntax or memory error, returns NULL.
 */
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
