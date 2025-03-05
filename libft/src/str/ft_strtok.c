/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:36:13 by mmarinov          #+#    #+#             */
/*   Updated: 2025/03/04 14:23:20 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static char	*skip_delimiters(char *str, const char *delim)
{
	while (*str && ft_strchr(delim, *str))
		str++;
	return (str);
}

static char	*handle_quotes(char *str)
{
	char	quote;

	quote = *str;
	str++;
	while (*str && *str != quote)
		str++;
	if (*str)
		str++;
	return (str);
}

static char	*process_token(char *str, const char *delim)
{
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			str = handle_quotes(str);
		else if (ft_strchr(delim, *str))
			break ;
		else
			str++;
	}
	return (str);
}

char	*ft_strtok_quotes(char *str, const char *delim)
{
	static char	*last;
	char		*start;

	if (str == NULL)
		str = last;
	if (str == NULL || *str == '\0')
		return (NULL);
	str = skip_delimiters(str, delim);
	start = str;
	str = process_token(str, delim);
	if (*str)
	{
		*str = '\0';
		last = str + 1;
	}
	else
		last = NULL;
	return (start);
}
/*
int main()
{
    char str[] = "This is a 'test str' with \"quoted text\" and other tokens.";
    const char *delim = " ";  // Delimitador: espacio

    char *token = ft_strtok_quotes(str, delim);
    while (token != NULL)
    {
        ft_printf("Token: %s\n", token);
   // Llamar de nuevo con NULL para continuar tokenizando
        token = ft_strtok_quotes(NULL, delim);
    }

    return 0;
}*/
