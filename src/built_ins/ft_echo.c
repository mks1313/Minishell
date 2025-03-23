/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:14:06 by mmarinov          #+#    #+#             */
/*   Updated: 2025/03/23 17:45:15 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
 * Si el primer argumento es "-n", no hacer un salto de línea al final
 * Imprimir los argumento
 * Separar los tokens por espacios
 * Salto de línea al final (a menos que sea -n)
 */
void	ft_echo(t_tkn *tokens)
{
	if (tokens->next && ft_strcmp(tokens->next->value, "-n") == 0)
		tokens = tokens->next;
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD)
			ft_putstr_fd(tokens->value, 1);
		if (tokens->next)
			write(1, " ", 1);
		tokens = tokens->next;
	}
	write(1, "\n", 1);
}
