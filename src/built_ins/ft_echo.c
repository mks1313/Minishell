/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:14:06 by mmarinov          #+#    #+#             */
/*   Updated: 2025/03/03 22:36:10 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_echo(char **cmd)
{
	int	i;
	int	no_newline;

	no_newline = 0;
	i = 1;
	// Verificar si el primer argumento es -n para omitir el salto de línea al final
	if (cmd[i] && ft_strcmp(cmd[i], "-n") == 0)
	{
		no_newline = 1;
		i++;  // Saltar el argumento -n
	}
	// Imprimir los argumentos restantes separados por espacios
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1])  // Si no es el último argumento, imprimir un espacio
			ft_putstr_fd(" ", 1);
		i++;
	}
	// Si no se especificó la opción -n, imprimir un salto de línea al final
	if (!no_newline)
		ft_putstr_fd("\n", 1);

	return (0);
}
