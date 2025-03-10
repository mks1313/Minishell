/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:04:41 by mmarinov          #+#    #+#             */
/*   Updated: 2025/03/10 18:00:59 by mmarinov         ###   ########.fr       */
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
			char *token_value = ft_substr(line, start - line, str - start);
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

/*
t_tkn *tokenize_input(char *line)
{
    t_tkn *tokens = NULL;   // Lista de tokens resultante
    char *token;
    t_tkn *current_token;

    token = ft_strtok_quotes(line, " \t"); // Usa ft_strtok_quotes para dividir por espacios y tabulaciones
    while (token != NULL)
    {
        // Clasifica el token y agrega a la lista
        t_tkn *new_token = malloc(sizeof(t_tkn));
        if (new_token == NULL)
            return (NULL); // Manejo de error de memoria

        new_token->value = ft_strdup(token);  // Crea una copia del token
        new_token->type = TOKEN_WORD; // Clasificación básica, puedes agregar más lógica
        new_token->opertype = OP_UNSET;  // Ajustar según el tipo de operador si es necesario
        new_token->terminated = true;  // Marcar como terminado
        new_token->next = NULL;
        // Agrega el token a la lista
        if (tokens == NULL)
            tokens = new_token;
        else
        {
            current_token = tokens;
            while (current_token->next != NULL)
                current_token = current_token->next;
            current_token->next = new_token;
        }
        token = ft_strtok_quotes(NULL, " \t");
    }
    return tokens;  // Retorna la lista de tokens
}*/
