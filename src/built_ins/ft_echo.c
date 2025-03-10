/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:14:06 by mmarinov          #+#    #+#             */
/*   Updated: 2025/03/10 17:09:42 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_tkn *tokens)
{
	// Si el primer argumento es "-n", no hacer un salto de línea al final
	if (tokens->next && ft_strcmp(tokens->next->value, "-n") == 0)
		tokens = tokens->next;

	// Imprimir los argumentos
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD)
			ft_putstr_fd(tokens->value, 1);
		if (tokens->next)
			write(1, " ", 1);  // Separar los tokens por espacio
		tokens = tokens->next;
	}
	write(1, "\n", 1);  // Salto de línea al final (a menos que sea -n)
}
