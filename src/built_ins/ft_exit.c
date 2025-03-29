/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:13:55 by mmarinov          #+#    #+#             */
/*   Updated: 2025/03/23 17:34:38 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Verificar si un string es numérico
// Permitir signos
static int	is_numeric_argument(const char *str)
{
	int	i;

	if (str[0] == '-' || str[0] == '+')
		i = 1;
	else
		i = 0;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (0);
	return (1);
}

// Manejar el valor de salida y la validación de argumentos
int	ft_exit(char **cmd)
{
	int	exit_code;

	ft_putstr_fd("exit\n", 1);
	if (!cmd)
		return (0);
	if (cmd[1] && cmd[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (EXIT_TOO_MANY_ARGS);
	}
	if (cmd[1] && !is_numeric_argument(cmd[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (EXIT_NON_NUMERIC_ARG);
	}
	if (cmd[1])
		exit_code = ft_atoi(cmd[1]);
	else
		exit_code = EXIT_SUCCESS_CODE;
	return (exit_code);
}
