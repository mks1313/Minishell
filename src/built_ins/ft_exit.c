/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:13:55 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/16 14:12:16 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Verifica si el argumento es un número válido
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

// Muestra el error de argumento no numérico
static void	print_numeric_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

// Realiza la salida del shell
static void	exit_shell(t_shell *shell, int exit_code)
{
	free_data(shell);
	exit(exit_code);
}

void	ft_exit(t_cmd *cmd, t_shell *shell)
{
	char	**args;
	int		arg_count;

	args = cmd->args;
	arg_count = 0;
	while (args && args[arg_count])
		arg_count++;
	if (arg_count == 1)
		exit_shell(shell, EXIT_SUCCESS);
	if (arg_count > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return ;
	}
	if (!is_numeric_argument(args[1]))
	{
		print_numeric_error(args[1]);
		exit_shell(shell, 2);
	}
	exit_shell(shell, ft_atol(args[1]) % 256);
}
