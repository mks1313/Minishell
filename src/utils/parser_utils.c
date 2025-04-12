/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:53:56 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/12 20:57:09 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_input(const char *input, t_env *env, int l_e_s)
{
	t_tkn	*tokens;

	tokens = tokenize_input((char *)input);
	if (!tokens)
	{
		// Manejar error si la tokenización falla
		return ;
	}
	// Paso 2: Expansión de variables sobre los tokens
	expand_variable(tokens, env, l_e_s);
	// Paso 3: Aquí  agregar la lógica para el parsing de comandos y ejecución
}
