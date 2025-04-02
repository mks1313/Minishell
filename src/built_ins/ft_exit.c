/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:13:55 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/02 16:20:07 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <limits.h>

// Función auxiliar: verifica si el argumento es un número válido
static int	is_numeric_argument(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i = 1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

// Función para manejar la salida del shell correctamente
void	exit_shell(t_shell *shell, int exit_code)
{
	free_data(shell); // Liberar memoria antes de salir
	exit(exit_code);
}

void	ft_exit(t_tkn *tokens, t_shell *shell)
{
	long	exit_code;
	int		arg_count = 0;
	char	*cmd_args[2] = {NULL, NULL};  // Solo necesitamos un argumento para 'exit'

	t_tkn *current = tokens->next;  // Saltamos el primer token que es "exit"
	while (current)
	{
		arg_count++;
		current = current->next;
	}
	if (arg_count == 0)
	{
		exit_shell(shell, EXIT_SUCCESS);
	}
	if (arg_count > 1)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return;
	}
	cmd_args[0] = tokens->next->value;  // El primer argumento de "exit"
	if (!is_numeric_argument(cmd_args[0]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd_args[0], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_shell(shell, 2);
	}
	exit_code = ft_atol(cmd_args[0]);
	exit_code %= 256;  // Normalizar el código de salida
	if (exit_code < 0)
		exit_code += 256;
	exit_shell(shell, exit_code);
}
