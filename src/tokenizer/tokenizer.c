/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:04:41 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/18 17:36:27 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_quoted_token(t_tkn **token, char **str)
{
	t_tkn	*new_token;
	char	*start;

	start = *str;
	new_token = create_token(NULL, TOK_WORD);
	*str = handle_quotes(*str, new_token);
	if (!*str)
	{
		free(new_token);
		ft_putendl_fd("syntax error: unclosed quote", STDERR_FILENO);
		return (0);
	}
	add_token_to_list(token, new_token, start, *str);
	printf("Token(q_q): %s, Type: %d\n", new_token->value, new_token->type);
	return (1);
}

static int	handle_normal_token(t_tkn **token, char **str)
{
	t_tkn	*new_token;
	char	*start;

	start = *str;
	new_token = create_token(NULL, TOK_WORD);
	*str = process_non_quotes(*str);
	add_token_to_list(token, new_token, start, *str);
	printf("Token(no_q): %s, Type: %d\n", new_token->value, new_token->type);
	return (1);
}

static int	process_token(t_tkn **token, char **str)
{
	*str = skip_delimiters(*str, " \t\n");
	if (**str == '\0')
		return (0);
	if (**str == '\'' || **str == '\"')
		return (handle_quoted_token(token, str));
	else
		return (handle_normal_token(token, str));
}

t_tkn	*tokenize_input(char *line)
{
	t_tkn	*token[2];
	 char	*str;

	token[HEAD] = NULL;
	token[TAIL] = NULL;
	str = line;
	while (*str)
	{
		if (!process_token(token, &str))
		{
			ft_free_tokens(token[HEAD]);
			return (NULL);
		}
	}
	return (token[HEAD]);
}
