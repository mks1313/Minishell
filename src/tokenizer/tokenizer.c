/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:04:41 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/15 18:38:19 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tkn	*create_token(char *value, int type)
{
	t_tkn	*new_token;

	new_token = (t_tkn *)malloc(sizeof(t_tkn));
	if (!new_token)
		return (NULL);
	new_token->value = value;
	new_token->type = type;
	new_token->single_quote = false;
	new_token->double_quote = false;
	new_token->next = NULL;
	return (new_token);
}

static char	*handle_quotes(char *str, t_tkn *token)
{
	char	quote;

	quote = *str;
	str++;
	if (quote == '\'')
		token->single_quote = true;
	else if (quote == '\"')
		token->double_quote = true;
	while (*str && *str != quote)
		str++;
	if (*str == '\0')
	{
		ft_putstr_fd("syntax error: unexpected EOF while matching quote\n", 2);
		return (NULL);
	}
	return (str + 1);
}

static char	*process_non_quotes(char *str)
{
	if (ft_strchr(" ;|&", *str))
		str++;
	else
	{
		while (*str && !ft_strchr(" ;|&'\" \t\n", *str))
			str++;
	}
	return (str);
}

static void	add_token_to_list(t_tkn **token, t_tkn *new_token, char *line, char *start, char *str)
{
	char	*token_value;

	token_value = ft_substr(line, start - line, str - start);
	if (!token_value)
		return ;
	new_token->value = token_value;
	if (!token[HEAD])
		token[HEAD] = new_token;
	else
		token[TAIL]->next = new_token;
	token[TAIL] = new_token;
}

t_tkn	*tokenize_input(char *line)
{
	t_tkn	*token[2];
	t_tkn	*new_token;
	char	*start;
	char	*str;

	token[HEAD] = NULL;
	token[TAIL] = NULL;
	str = line;
	while (*str)
	{
		str = skip_delimiters(str, " \t\n");
		if (*str == '\0')
			break ;
		start = str;
		if (*str == '\'')
		{
			new_token = create_token(NULL, TOK_WORD);
			str = handle_quotes(str, new_token);
			if (!str)
			{
				ft_putendl_fd("syntax error: unclosed quote", STDERR_FILENO);
				ft_free_tokens(token[HEAD]);
				return (NULL);
			}
			add_token_to_list(token, new_token, line, start, str);
		}
		else if (*str == '\"')
		{
			new_token = create_token(NULL, TOK_WORD);
			str = handle_quotes(str, new_token);
			if (!str)
			{
				ft_putendl_fd("syntax error: unclosed quote", STDERR_FILENO);
				ft_free_tokens(token[HEAD]);
				return (NULL);
			}
			add_token_to_list(token, new_token, line, start, str);
		}
		else
		{
			new_token = create_token(NULL, TOK_WORD);
			str = process_non_quotes(str);
			add_token_to_list(token, new_token, line, start, str);
		}
	}
	return (token[HEAD]);
}
