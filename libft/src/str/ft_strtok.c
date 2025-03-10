/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:36:13 by mmarinov          #+#    #+#             */
/*   Updated: 2025/03/10 19:11:14 by mmarinov         ###   ########.fr       */
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

	quote = *str;  // Guarda el tipo de comilla (simples o dobles)
	str++;  // Avanza después de la comilla de apertura
	while (*str && *str != quote)  // Avanza hasta encontrar la comilla de cierre
		str++;
	if (*str)  // Si encontramos la comilla de cierre, saltamos la comilla
		str++;
	return (str);
}

static char	*process_token(char *str, const char *delim)
{
	while (*str)
	{
		// Si encontramos una comilla simple o doble, saltamos las comillas
		if (*str == '\'' || *str == '\"')
			str = handle_quotes(str);
		// Si encontramos un delimitador, terminamos
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
		str = last;  // Si no se pasa una nueva cadena, usamos la última procesada
	if (str == NULL || *str == '\0')  // Si la cadena está vacía, retornamos NULL
		return (NULL);

	str = skip_delimiters(str, delim);  // Salta los delimitadores al principio
	start = str;  // Guardamos el inicio del token

	str = process_token(str, delim);  // Procesamos el token hasta encontrar un delimitador

	// Si encontramos un delimitador, lo reemplazamos por '\0' y actualizamos `last`
	if (*str)
	{
		*str = '\0';  // Terminamos el token
		last = str + 1;  // Apuntamos a la siguiente posición para la próxima llamada
	}
	else
		last = NULL;  // Si no hay más tokens, dejamos `last` como NULL

	return (start);  // Devolvemos el token procesado
}
