/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:04:41 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/27 18:28:53 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_token_segment(char **str, bool *s_quote, bool *db_quote)
{
	char	*buffer;
	char	quote;
	char	*tmp;

	buffer = ft_calloc(1, 1);
	if (!buffer)
		return (NULL);
	*s_quote = false;
	*db_quote = false;

	while (**str && !ft_strchr(" \t\n|<>", **str))
	{
		if (**str == '\'' || **str == '"')
		{
			quote = *(*str)++;
			if (quote == '\'')
				*s_quote = true;
			else if (quote == '"')
				*db_quote = true;
			while (**str && **str != quote)
			{
				tmp = ft_substr(*str, 0, 1);
				if (!tmp)
					return (free(buffer), NULL);
				buffer = ft_strjoin_free(buffer, tmp);
				free(tmp);
				(*str)++;
			}
			if (**str == quote)
				(*str)++;
		}
		else
		{
			tmp = ft_substr(*str, 0, 1);
			if (!tmp)
				return (free(buffer), NULL);
			buffer = ft_strjoin_free(buffer, tmp);
			free(tmp);
			(*str)++;
		}
	}
	return (buffer);
}

static int	process_token(t_tkn **token, char **str)
{
	char	*accum;
	char	*seg;
	bool	sq;
	bool	dq;
	char	*tmp;
	t_tkn	*new;

	accum = ft_strdup("");
	if (!accum)
		return (0);
	skip_delimiters(str);
	if (**str == '\0')
		return (free(accum), 0);
	while (**str && !ft_strchr(" \t\n|<>", **str))
	{
		seg = read_token_segment(str, &sq, &dq);
		if (!seg)
			return (free(accum), 0);
		tmp = ft_strjoin(accum, seg);
		free(accum);
		free(seg);
		accum = tmp;
	}
	new = create_token(accum, TOK_WORD);
	new->s_quote = sq;
	new->db_quote = dq;
	add_token_to_list(token, new, accum, accum + ft_strlen(accum));
	free(accum);
	return (1);
}

static void debug(t_tkn *head)
{
	t_tkn	*curr = head;
		while (curr)
		{
			ft_printf("Token: [%s], Type: %d\n", curr->value, curr->type);
			curr = curr->next;
		}
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
	debug(token[HEAD]);
	return (token[HEAD]);
}
