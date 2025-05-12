/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:04:41 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/12 16:23:13 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tkn	*tokenize_input(char *line)
{
	t_tkn		*head;
	t_tkn		*tail;
	t_tkn		*new;
	char		*str;

	head = NULL;
	tail = NULL;
	str = line;
	while (*str)
	{
		while (*str == ' ' || *str == '\t')
			str++;
		if (!*str)
			break ;
		if (ft_strchr("|<>", *str))
			new = read_operator(&str);
		else
			new = read_token(&str);
		if (!new)
			return (ft_free_tokens(head), NULL);
		if (!head)
			head = new;
		else
			tail->next = new;
		tail = new;
	}
	return (head);
}
