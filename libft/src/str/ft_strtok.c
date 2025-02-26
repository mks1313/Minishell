/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:36:13 by mmarinov          #+#    #+#             */
/*   Updated: 2025/02/26 16:40:35 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok_quotes(char *str, const char *delim)
{
	static char	*last;
	char		*start;
	char		quote = '\0';  // Para manejar las comillas simples o dobles

	if (str == NULL)
		str = last;
	if (str == NULL || *str == '\0')
		return (NULL);

	// Ignorar delimitadores iniciales fuera de comillas
	while (*str && ft_strchr(delim, *str))
		str++;
	// Guardar el inicio del token
	start = str;
	// Recorrer hasta encontrar el fin del token
	while (*str)
	{
		if (*str == '\'' || *str == '\"')  // Detectar si empieza con comillas
		{
			quote = *str;
			str++;
			// Buscar el cierre de la comilla
			while (*str && *str != quote)
				str++;
			// Si encontramos el cierre de la comilla, seguimos
			if (*str)
				str++;
		}
		else if (ft_strchr(delim, *str))  // Detectar fin del token fuera de comillas
			break;
		else
			str++;
	}
	// Si encontramos un delimitador, lo reemplazamos por '\0'
	if (*str)
	{
		*str = '\0';
		last = str + 1;
	}
	else
		last = NULL;
	return (start);
}
