/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:04:41 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/13 12:12:20 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_next_token(char **str, t_tkn **head, t_tkn **tail)
{
	t_tkn	*new;

	while (**str == ' ' || **str == '\t')
		(*str)++;
	if (!**str)
		return (0);
	if (ft_strchr("|<>", **str))
		new = read_operator(str);
	else
		new = read_token(str);
	if (!new)
		return (-1);
	if (!*head)
		*head = new;
	else
		(*tail)->next = new;
	*tail = new;
	return (1);
}

t_tkn	*tokenize_input(char *line)
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
		status = process_next_token(&str, &head, &tail);
		if (status == -1)
			return (ft_free_tokens(head), NULL);
		if (status == 0)
			break ;
	}
	return (head);
}
