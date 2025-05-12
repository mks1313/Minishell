/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:34:23 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/10 13:30:53 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/**
 * create_token - Creates and initializes a new token structure
 * @value: The string value of the token (can be NULL)
 * @type: The type of token (enum t_tkn_type)
 *
 * Allocates memory for a new token and initializes all its fields.
 * Uses ft_calloc instead of malloc to ensure zero-initialized memory.
 * Handles memory allocation failures gracefully.
 *
 * Return: Pointer to the new token, or NULL if allocation fails
 */
t_tkn	*create_token(char *value, t_tkn_type type)
{
	t_tkn	*new_token;

	new_token = (t_tkn *)ft_calloc(1, sizeof(t_tkn));
	if (!new_token)
		return (NULL);
	if (value)
	{
		new_token->value = ft_strdup(value);
		if (!new_token->value)
			return (free(new_token), NULL);
	}
	new_token->type = type;
	return (new_token);
}

void	add_token_to_list(t_tkn **tkn, t_tkn *new_tkn, char *start, char *end)
{
	char	*token_value;

	token_value = ft_substr(start, 0, end - start);
	if (!token_value)
	{
		free(new_tkn);
		return ;
	}
	if (new_tkn->value)
		free(new_tkn->value);
	new_tkn->value = token_value;
	if (!tkn[HEAD])
		tkn[HEAD] = new_tkn;
	else
		tkn[TAIL]->next = new_tkn;
	tkn[TAIL] = new_tkn;
}
