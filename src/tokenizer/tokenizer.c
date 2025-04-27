/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:04:41 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/27 12:30:51 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_token_segment(char **str, t_tkn *token)
{
	char	*start;
	char	*result;
	char	*temp;
	char	quote;

	start = *str;
	result = NULL;
	token->s_quote = false;
	token->db_quote = false;
	if (**str == '\'' || **str == '"')
	{
		quote = *(*str)++;
		if (quote == '\'')
			token->s_quote = true;
		if (quote == '"')
			token->db_quote = true;

		while (**str && **str != quote)
		{
			if (**str == '\\' && quote == '"')
				(*str)++;
			(*str)++;
		}
		if (**str == quote)
			(*str)++;
	}
	else
	{
		while (**str && !ft_strchr(" \t\n|<>\"\'", **str))
		{
			if (**str == '\\' && *(*str + 1)) (*str)++;
			(*str)++;
		}
	}
	temp = ft_substr(start, 0, *str - start);
	if (!temp)
		return (NULL);
	result = temp;
	return (result);
}

static int	process_token(t_tkn **token, char **str)
{
	char	*accum = ft_strdup("");
	char	*seg;
	bool	sq, dq;

	skip_delimiters(str);
	if (**str == '\0')
		return (0);
	while (**str && !ft_strchr(" \t\n|<>", **str))
	{
		seg = read_token_segment(str, token);
		if (!seg)
		{
			free(accum);
			return (0);
		}
		char *tmp = ft_strjoin(accum, seg);
		free(accum);
		free(seg);
		accum = tmp;
	}
	t_tkn *new = create_token(accum, TOK_WORD);
	new->s_quote = sq;
	new->db_quote = dq;
	add_token_to_list(token, new, accum, accum + ft_strlen(accum));
	free(accum);
	return (1);
}

t_tkn	*tokenize_input(char *line)
{
	t_tkn	*token[2];
	char	*str;

	token[HEAD] = NULL;
	token[TAIL] = NULL;
	str = line;
	printf("== Tokenizing line: [%s] ==\n", line);
	while (*str)
	{
		skip_delimiters(&str);
		if (*str == '\0')
			break ;
		if (!process_token(token, &str))
		{
			printf("Tokenization failed\n");
			ft_free_tokens(token[HEAD]);
			return (NULL);
		}
	}
	printf("== Tokenization complete ==\n");
	return (token[HEAD]);
}
