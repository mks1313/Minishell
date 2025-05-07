/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:04:41 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/07 13:26:45 by mmarinov         ###   ########.fr       */
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

static int	process_operator_token(t_tkn **token, char **str)
{
	t_tkn	*new;
	char	op[3] = {0};

	if (**str == '>' && *(*str + 1) == '>')
	{
		op[0] = '>';
		op[1] = '>';
		*str += 2;
		new = create_token(op, TOK_APPEND);
	}
	else if (**str == '<' && *(*str + 1) == '<')
	{
		op[0] = '<';
		op[1] = '<';
		*str += 2;
		new = create_token(op, TOK_HEREDOC);
	}
	else if (**str == '>')
	{
		op[0] = '>';
		*str += 1;
		new = create_token(op, TOK_REDIR_OUT);
	}
	else if (**str == '<')
	{
		op[0] = '<';
		*str += 1;
		new = create_token(op, TOK_REDIR_IN);
	}
	else if (**str == '|')
	{
		op[0] = '|';
		*str += 1;
		new = create_token(op, TOK_PIPE);
	}
	else
		return (0);
	if (!new)
		return (0);
	add_token_to_list(token, new, op, op + ft_strlen(op));
	return (1);
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
		skip_delimiters(&str);
		if (*str == '\0')
			break ;
		if (ft_strchr("|<>", *str))
		{
			if (!process_operator_token(token, &str))
				return (ft_free_tokens(token[HEAD]), NULL);
		}
		else
			if (!process_token(token, &str))
				return (ft_free_tokens(token[HEAD]), NULL);
	}
	return (token[HEAD]);
}
