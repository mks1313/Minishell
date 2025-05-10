/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:04:41 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/10 16:38:17 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_token_segment(char **str, t_tkn_quote *quote_type)
{
	char	*buffer;
	char	*tmp;
	char	quote;
	bool	has_sq;
	bool	has_dq;

	has_sq = false;
	has_dq = false;
	buffer = ft_calloc(1, 1);
	if (!buffer)
		return (NULL);
	while (**str && !ft_strchr(" \t\n|<>", **str))
	{
		if (**str == '\'' || **str == '"')
		{
			quote = *(*str)++;
			if (quote == '\'')
				has_sq = true;
			else if (quote == '"')
				has_dq = true;
			while (**str && **str != quote)
			{
				tmp = ft_substr(*str, 0, 1);
				if (!tmp)
					return (free(buffer), NULL);
				buffer = ft_strjoin_free(buffer, tmp);
				free(tmp);
				(*str)++;
			}
			if (**str != quote)
			{
				ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
				return (free(buffer), NULL);
			}
			(*str)++;
		}
		else if (**str == '\\')
		{
			(*str)++;
			if (!**str)
			{
				ft_putstr_fd("minishell: syntax error: invalid escape\n", 2);
				return (free(buffer), NULL);
			}
			tmp = ft_substr(*str, 0, 1);
			buffer = ft_strjoin_free(buffer, tmp);
			free(tmp);
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
	if (has_sq && has_dq)
		*quote_type = Q_MIX;
	else if (has_sq)
		*quote_type = Q_SINGLE;
	else if (has_dq)
		*quote_type = Q_DOUBLE;
	else
		*quote_type = Q_NONE;
	return (buffer);
}

static int	process_token(t_tkn **token, char **str)
{
	char			*accum;
	char			*seg;
	t_tkn_quote		quote = Q_NONE, temp_quote;
	t_tkn			*new;
	char			*tmp;

	accum = ft_strdup("");
	if (!accum)
		return (0);
	while (**str && !ft_strchr(" \t\n|<>", **str))
	{
		seg = read_token_segment(str, &temp_quote);
		if (!seg)
			return (free(accum), 0);
		if (quote != temp_quote && quote != Q_NONE)
			quote = Q_MIX;
		else if (quote == Q_NONE)
			quote = temp_quote;
		tmp = ft_strjoin(accum, seg);
		free(accum);
		free(seg);
		accum = tmp;
	}
	new = create_token(accum, TOK_WORD);
	new->quote = quote;
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
	t_tkn	*token[2] = {NULL, NULL};
	char	*str = line;

	while (*str)
	{
		skip_delimiters(&str);
		if (*str == '\0')
			break;
		if (ft_strchr("|<>", *str))
		{
			if (!process_operator_token(token, &str))
				return (ft_free_tokens(token[HEAD]), NULL);
		}
		else
		{
			if (!process_token(token, &str))
				return (ft_free_tokens(token[HEAD]), NULL);
		}
	}
	return (token[HEAD]);
}
