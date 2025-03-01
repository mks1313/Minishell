/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:43:35 by mmarinov          #+#    #+#             */
/*   Updated: 2025/03/01 14:24:31 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Pasamos un puntero al entorno a la función
char	*ft_getenv(const char *name, char **envp)
{
	int		i;
	size_t	len;

	// Si no se pasa un nombre de variable de entorno, retornar NULL
	if (!name)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	// Recorrer el arreglo de entorno (envp) manualmente
	while (envp[i])
	{
		// Cada variable de entorno tiene formato "NOMBRE=VALOR"
		// Comparar si "NOMBRE" coincide con el nombre proporcionado
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
		{
			// Retornar el valor después del signo '='
			return (envp[i] + len + 1);
		}
		i++;
	}
	// Si no se encontró la variable, retornar NULL
	return (NULL);
}
/*
   int	main(int argc, char *argv[], char *envp[])
   {
   ft_getenv("PATH", envp);
   (void)argc;
   (void)argv;
   }
   */
