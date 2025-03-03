/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:29:55 by mmarinov          #+#    #+#             */
/*   Updated: 2025/03/03 22:31:59 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_cd(char **cmd)
{
	char *path;
	path = cmd[1];

	if (cmd[1] == NULL) // Si no se pasa un directorio, no se hace nada (podemos agregar un mensaje de error si se requiere)
	{
		ft_putstr_fd("minishell: cd: No path specified\n", 2);
		return (1);
	}
	// Verificamos si la ruta contiene '~' y la rechazamos
	if (strchr(path, '~'))
	{
		ft_putstr_fd("minishell: cd:~ not supported.Use abs or rel paths\n", 2);
		return (1);
	}
	// Si la ruta es absoluta (comienza con '/')
	if (path[0] == '/')
	{
		if (chdir(path) != 0) // Intentamos cambiar al directorio
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (1);
		}
	}
	// Si la ruta es relativa (no comienza con '/')
	else
	{
		if (chdir(path) != 0) // Intentamos cambiar al directorio
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (1);
		}
	}
	return (0); // Cambio de directorio exitoso
}
