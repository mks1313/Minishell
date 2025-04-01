/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:27:39 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/01 17:32:38 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Función para crear un nuevo nodo t_tkn
t_tkn	*new_token(char *value, t_tkn_type type)
{
	t_tkn	*token;

	token = malloc(sizeof(t_tkn));
	if (!token)
		return (NULL);
	token->value = strdup(value); // Duplicamos el valor del token
	token->type = type;
	token->terminated = false; // Se puede usar para EOF en el futuro
	token->next = NULL;
	return (token);
}

// Función para añadir un token a la lista enlazada
void	add_token(t_tkn **tokens, const char *start, int len, t_tkn_type type)
{
	t_tkn	*new;
	t_tkn	*last;

	if (len == 0)
		return ;
	new = new_token(strndup(start, len), type); // Directo a new_token
	if (!new)
		return ;
	if (!*tokens)
		*tokens = new;
	else
	{
		last = *tokens;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

t_tkn	*lexer(const char *input)
{
	t_tkn	*tokens = NULL;
	const char	*ptr = input;
	const char	*start = NULL;
	int		in_quo = 0;
	char	quo_char = '\0';

	while (*ptr)
	{
		if ((*ptr == '"' || *ptr == '\'') && (in_quo == 0 || *ptr == quo_char))
		{
			if (in_quo)
			{
				in_quo = 0;
				ptr++;
				add_token(&tokens, start, ptr - start, *start == '"' ? TOKEN_DQUOTE : TOKEN_QUOTE);
				start = NULL;
			}
			else
			{
				in_quo = 1;
				quo_char = *ptr;
				start = ptr;
			}
		}
		else if (!in_quo && (*ptr == ' ' || *ptr == '|'
					|| *ptr == '<' || *ptr == '>'))
		{
			if (start)
			{
				add_token(&tokens, start, ptr - start, TOKEN_WORD);
				start = NULL;
			}
			if (*ptr != ' ')
			{
				t_tkn_type type = TOKEN_OPERATOR;
				if (*ptr == '<' && *(ptr + 1) == '<')
					add_token(&tokens, ptr++, 2, TOKEN_OPERATOR);
				else if (*ptr == '>' && *(ptr + 1) == '>')
					add_token(&tokens, ptr++, 2, TOKEN_OPERATOR);
				else
					add_token(&tokens, ptr, 1, type);
			}
		}
		else
		{
			if (!start)
				start = ptr;
		}
		ptr++;
	}
	if (start)
		add_token(&tokens, start, ptr - start, TOKEN_WORD);
	return (tokens);
}

void	print_tokens(t_tkn *tokens)
{
	while (tokens)
	{
		printf("Token: [%s] - Type: %d\n", tokens->value, tokens->type);
		tokens = tokens->next;
	}
}
