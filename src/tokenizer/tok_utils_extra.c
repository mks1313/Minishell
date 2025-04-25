/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:45:00 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/25 13:35:22 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Lee un segmento escapando caracteres si es necesario
char	*read_escaped_segment(char **str, char quote)
{
	char	buffer[1024];
	int		i = 0;

	while (**str && (quote ? **str != quote : !ft_strchr(" \t\n|<>\"\'", **str)))
	{
		if (**str == '\\')
		{
			(*str)++;
			if (**str)
				buffer[i++] = *(*str)++;
		}
		else
			buffer[i++] = *(*str)++;
	}
	buffer[i] = '\0';
	return (ft_strdup(buffer));
}

// Llama a read_escaped_segment y marca flags de comillas
char	*read_token_segment(char **str, bool *s_quote, bool *db_quote)
{
	char	*result = NULL;
	char	quote;

	*s_quote = false;
	*db_quote = false;
	if (**str == '\'' || **str == '"')
	{
		quote = *(*str)++;
		if (quote == '\'') *s_quote = true;
		if (quote == '"') *db_quote = true;
		result = read_escaped_segment(str, quote);
		if (**str == quote)
			(*str)++;
	}
	else
	{
		result = read_escaped_segment(str, 0);
	}
	return (result);
}
