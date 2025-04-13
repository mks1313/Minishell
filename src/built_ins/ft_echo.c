/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:14:06 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/13 15:33:07 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Saltamos el primer token, ya que es el comando 'echo'
 * Verificamos si hay opcion -n
 * Imprimir argumentos, si hay mas tokens separlos por un espacio
 * Salto de linea solo si no se encontro -n
 */

static int	is_n_option(const char *arg)
{
	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	for (int i = 2; arg[i]; i++)
		if (arg[i] != 'n')
			return (0);
	return (1);
}

void	ft_echo(t_cmd *cmd)
{
	int		i = 1;
	int		newline = 1;

	// detectar si hay una o varias opciones -n
	while (cmd->args[i] && is_n_option(cmd->args[i]))
	{
		newline = 0;
		i++;
	}

	// imprimir los argumentos restantes
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}

	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

