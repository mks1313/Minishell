/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:43:35 by mmarinov          #+#    #+#             */
/*   Updated: 2025/03/10 18:22:54 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(const char *name, t_env *env)
{
	t_env	*current;
	size_t	len;

	/* Si no se pasa un nombre de variable de entorno, retornar NULL */
	if (!name)
		return (NULL);
	len = ft_strlen(name);
	current = env;

	/* Recorrer la lista de entorno */
	while (current)
	{
		/* Comparar si "key" coincide con el nombre proporcionado */
		if (ft_strncmp(current->key, name, len) == 0 && current->key[len] == '\0')
		{
			/* Retornar el valor asociado */
			return (current->value);
		}
		current = current->next;
	}
	/* Si no se encontró la variable, retornar NULL */
	return (NULL);
}
