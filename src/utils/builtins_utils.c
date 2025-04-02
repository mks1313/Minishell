/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:13:43 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/02 14:25:24 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/**
 * @brief Duplica una cadena con verificación segura para NULL
 * 
 * Esta función verifica si la cadena de entrada es NULL antes de
 * intentar duplicarla, para evitar errores de segmentación.
 * 
 * @param s Cadena a duplicar
 * @return Copia de la cadena o cadena vacía si s es NULL
 */
char	*safe_strdup(const char *s)
{
	if (!s)
		return (ft_strdup(""));
	return (ft_strdup(s));
}

/**
 * @brief Imprime un mensaje de error para comandos builtin
 * 
 * @param cmd Nombre del comando
 * @param arg Argumento que causó el error
 * @param msg Mensaje de error
 */
void	builtin_error(char *cmd, char *arg, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	if (arg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(arg, 2);
	}
	if (msg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(msg, 2);
	}
	ft_putstr_fd("\n", 2);
}
