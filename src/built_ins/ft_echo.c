/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:14:06 by mmarinov          #+#    #+#             */
/*   Updated: 2025/03/29 13:43:09 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
 * Si el primer argumento es "-n", no hacer un salto de línea al final
 * Imprimir los argumento
 * Separar los tokens por espacios
 * Salto de línea al final (a menos que sea -n)
 */

/*
 * Saltamos el primer token, ya que es el comando 'echo'
 * Verificamos si hay opcion -n
 * Imprimir argumentos, si hay mas tokens separlos por un espacio
 * Salto de linea solo si no se encontro -n
 */
void	ft_echo(t_tkn *tokens)
{
	int	option_n;

	if (!tokens)
		return ;;
	option_n = 0;
	tokens = tokens->next;
	if (tokens && ft_strcmp(tokens->value, "-n") == 0)
	{
		option_n = 1;
		tokens = tokens->next;
	}
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD)
			ft_putstr_fd(tokens->value, 1);
		if (tokens->next)
			write(1, " ", 1);
		tokens = tokens->next;
	}
	if (!option_n)
		write(1, "\n", 1);
}

