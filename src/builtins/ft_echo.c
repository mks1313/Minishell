/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:14:06 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/03 18:53:15 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Saltamos el primer token, ya que es el comando 'echo'
 * Verificamos si hay opcion -n
 * Imprimir argumentos, si hay mas tokens separlos por un espacio
 * Salto de linea solo si no se encontro -n
 */
static int	is_valid_n_flag(const char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static void	print_arguments(char	**args, int i)
{
	if (!args)
		return ;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
}

static int	parse_echo_flags(char **args, int *newline)
{
	int	i;

	i = 1;
	*newline = 1;
	while (args[i] && is_valid_n_flag(args[i]))
	{
		*newline = 0;
		i++;
	}
	return (i);
}

void	ft_echo(t_cmd *cmd)
{
	int	newline;

	if (!cmd || !cmd->args)
		return ;
	print_arguments(cmd->args, parse_echo_flags(cmd->args, &newline));
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
