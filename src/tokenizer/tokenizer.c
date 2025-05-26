/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:04:41 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/26 14:09:03 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Parses the next token from the input string.
 * - Skips whitespace.
 * - If the next char is an operator (|, <, >), calls read_operator().
 * - Otherwise, calls read_token() to process a word or sequence.
 * - Links the new token to the list by updating head and tail.
 *
 * Returns:
 *   - 1 if a token was successfully parsed and added.
 *   - 0 if the end of input was reached (no more tokens).
 *   - -1 if there was a syntax or memory error.
 */
static int	process_next_tkn(char **str, t_tkn **head, t_tkn **tail, t_shell *s)
{
	t_tkn	*new;

	while (**str == ' ' || **str == '\t')
		(*str)++;
	if (!**str)
		return (0);
	if (ft_strchr("|<>", **str))
		new = read_operator(str, s);
	else
		new = read_token(str, s);
	if (!new)
		return (-1);
	if (!*head)
		*head = new;
	else
		(*tail)->next = new;
	*tail = new;
	return (1);
}

/*
 * Main tokenizer entry point.
 * Takes a raw input line and tokenizes it into a linked list of t_tkn tokens.
 * Iteratively calls process_next_tkn() to extract tokens until the line ends.
 *
 * Returns:
 *   - The head of the token list.
 *   - NULL if an error occurred (syntax or allocation failure).
 */
t_tkn	*tokenize_input(char *line, t_shell *shell)
{
	t_tkn	*head;
	t_tkn	*tail;
	char	*str;
	int		status;

	head = NULL;
	tail = NULL;
	str = line;
	while (*str)
	{
		status = process_next_tkn(&str, &head, &tail, shell);
		if (status == -1)
			return (ft_free_tokens(head), NULL);
		if (status == 0)
			break ;
	}
	return (head);
}
