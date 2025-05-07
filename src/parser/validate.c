 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:00:00 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/07 12:00:00 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Verifica que un comando no esté vacío y tenga redirecciones válidas
 * Retorna 0 si el comando es inválido, 1 si es válido
 */
static int	validate_command_syntax(t_cmd *cmd)
{
	if (!cmd)
		return (0);
	
	// Caso especial: si solo hay redirecciones sin comando, es válido
	if (!cmd->cmd && cmd->redirs)
		return (1);
	
	// Un comando sin cmd ni redirecciones no es válido
	if (!cmd->cmd && !cmd->redirs)
		return (0);
	
	// Un comando vacío no es válido
	if (cmd->cmd && cmd->cmd[0] == '\0')
		return (0);
	
	return (1);
}

/*
 * Verifica que no haya pipes solitarios o al final sin comando siguiente
 * Retorna 0 si hay un error de sintaxis, 1 si todo es válido
 */
static int	validate_pipes(t_cmd *cmd_list)
{
	t_cmd	*curr;
	
	curr = cmd_list;
	while (curr && curr->next)
	{
		// Si el comando actual está vacío pero tiene un siguiente,
		// significa que hay un pipe solitario
		if (!validate_command_syntax(curr))
			return (0);
		
		curr = curr->next;
	}
	
	// Verificar el último comando (no debería ser vacío si hay pipes)
	if (curr && !validate_command_syntax(curr))
		return (0);
	
	return (1);
}

/*
 * Función principal que valida la sintaxis de la lista de comandos
 * Retorna 0 si hay un error de sintaxis, 1 si todo es válido
 */
int	validate_syntax(t_cmd *cmd_list)
{
	if (!cmd_list)
		return (1);  // Lista vacía es técnicamente válida
	
	// Validar pipes y comandos vacíos
	if (!validate_pipes(cmd_list))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (0);
	}
	
	return (1);
}