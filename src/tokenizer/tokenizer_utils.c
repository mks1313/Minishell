/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:34:23 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/27 12:04:52 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_tkn	*create_token(char *value, t_tkn_type type)
{
	t_tkn	*new_token;

	new_token = (t_tkn *)malloc(sizeof(t_tkn));
	if (!new_token)
		return (NULL);
	if (value)
		new_token->value = ft_strdup(value);
	else
		new_token->value = NULL;
	new_token->type = type;
	new_token->s_quote = false;
	new_token->db_quote = false;
	new_token->next = NULL;
	return (new_token);
}

char	*handle_quotes(char *str, t_tkn *token)
{
	char	quote;
	char	*tkn_val;
	char	*start;

	quote = *str;
	start = str + 1;
	str++;
	if (quote == '\'')
		token->s_quote = true;
	else if (quote == '\"')
		token->db_quote = true;
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	while (*str && *str != quote)
		str++;
	if (*str == '\0')
	{
		ft_putstr_fd("syntax error: unexpected EOF while matching quote\n", 2);
		return (NULL);
	}
	tkn_val = ft_substr(start, 0, str - start);
	if (!tkn_val)
		return (NULL);
	token->value = tkn_val;
	return (str + 1);
}

char	*process_non_quotes(char *str)
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
