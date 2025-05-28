/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:04:41 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/28 20:44:10 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Processes the next token from the input string.
 *
 * It skips whitespace and reads either an operator or a regular token.
 * It appends the new token to the token list and returns 1 on success,
 * -1 if there's an error, and 0 if the end of the string is reached.
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

/**
 * Tokenizes the input line into a list of tokens.
 *
 * It processes each part of the input, creating tokens for operators and words.
 * Returns the head of the token list or NULL if an error occurs.
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
