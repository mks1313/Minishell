/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:04:41 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/06 14:27:43 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tkn	*create_token(char *value, int type)
{
	t_tkn	*new_token;

	new_token = (t_tkn *)malloc(sizeof(t_tkn));
	if (!new_token)
		return (NULL);
	//new_token->value = ft_strdup(value);
	new_token->value = value;
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

static char	*handle_quotes(char *str)
{
	if (*str == '\'')
	{
		str++;
		while (*str && *str != '\'')
			str++;
		if (*str == '\'')
			str++;
	}
	else if (*str == '\"')
	{
		str++;
		while (*str && *str != '\"')
			str++;
		if (*str == '\"')
			str++;
	}
	return (str);
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

static void	add_token_to_list(t_tkn **token, char *line, char *start, char *str)
{
	t_tkn	*new_token;
	char	*token_value;

	token_value = ft_substr(line, start - line, str - start);
	if (!token_value)
		return ;
	new_token = create_token(token_value, TOK_WORD);
	if (!token[HEAD])
		token[HEAD] = new_token;
	else
		token[TAIL]->next = new_token;
	token[TAIL] = new_token;
}

t_tkn	*tokenize_input(char *line)
{
	t_tkn	*token[2];
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
		if (*str == '\'' || *str == '\"')
			str = handle_quotes(str);
		else
			str = process_non_quotes(str);
		if (start != str)
			add_token_to_list(token, line, start, str);
	}
	return (token[HEAD]);
}
