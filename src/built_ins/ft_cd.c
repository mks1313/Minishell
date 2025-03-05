/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:29:55 by mmarinov          #+#    #+#             */
/*   Updated: 2025/03/05 18:56:02 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_cd(char **cmd, t_data *data)
{
	char	*path;

	// Si no se pasa un argumento, mostramos un mensaje de error
	if (cmd[1] == NULL) {
		ft_putstr_fd("minishell: cd: No path specified\n", 2);
		return (1);
	}

	path = cmd[1];

	// Verificamos si la ruta contiene '~' y la rechazamos
	if (strchr(path, '~')) {
		ft_putstr_fd("minishell: cd: ~ not supported. Use absolute or relative paths\n", 2);
		return (1);
	}

	// Si la ruta es absoluta (comienza con '/')
	if (path[0] == '/') {
		if (chdir(path) != 0) {
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (1);
		}
	}
	// Si la ruta es relativa (no comienza con '/')
	else {
		if (chdir(path) != 0) {
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (1);
		}
	}

	// Actualizar el directorio actual en t_data
	if (data && data->cur_dir) {
		free(data->cur_dir);  // Libera la memoria de la ruta anterior si existe
	}

	// Guardamos el nuevo directorio actual en la estructura
	data->cur_dir = getcwd(NULL, 0);
	if (data->cur_dir == NULL) {
		ft_putstr_fd("minishell: cd: Error getting current directory\n", 2);
		return (1);
	}
	return (0);  // Cambio de directorio exitoso
}
