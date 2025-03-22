/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:04:41 by mmarinov          #+#    #+#             */
/*   Updated: 2025/03/22 16:49:29 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Función que crea un nuevo token de tipo WORD
t_tkn	*create_token(char *value, int type)
{
	t_tkn	*new_token;

	new_token = (t_tkn *)malloc(sizeof(t_tkn));
	if (!new_token)
		return (NULL);
	new_token->value = value;
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

// Función que maneja la tokenización de la entrada
t_tkn	*tokenize_input(char *line)
{
	t_tkn	*head = NULL;
	t_tkn	*tail = NULL;
	char	*start;
	char	*str = line;
	char	*token_value;

	while (*str)
	{
		// Saltar los delimitadores (espacios y otros caracteres no importantes)
		str = skip_delimiters(str, " \t\n");
		if (*str == '\0')
			break;
		start = str;
		// Manejar comillas simples
		if (*str == '\'')
		{
			str++;  // Saltamos la comilla inicial
			while (*str && *str != '\'')
				str++;
			if (*str == '\'')
				str++;  // Saltamos la comilla final
		}
		// Manejar comillas dobles
		else if (*str == '\"')
		{
			str++;  // Saltamos la comilla inicial
			while (*str && *str != '\"')
				str++;
			if (*str == '\"')
				str++;  // Saltamos la comilla final
		}
		// Si es un delimitador (por ejemplo, espacio o operador), terminamos el token
		else if (ft_strchr(" ;|&", *str))
		{
			str++;
		}
		// Si encontramos una palabra, avanzamos hasta el próximo delimitador
		else
		{
			while (*str && !ft_strchr(" ;|&'\" \t\n", *str))
				str++;
		}
		// Crear un token con la palabra o secuencia que acabamos de encontrar
		if (start != str)  // Solo si hay algo que tokenizar
		{
			token_value = ft_substr(line, start - line, str - start);
			if (!token_value)
			{
				//mabnejar logicca de eso;
				return (NULL);
			}
			t_tkn *new_token = create_token(token_value, TOKEN_WORD);
			// Agregar el token a la lista de tokens
			if (!head)
				head = new_token;
			else
				tail->next = new_token;
			tail = new_token;
		}
	}
	return head;
}
