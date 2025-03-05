/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:06:36 by mmarinov          #+#    #+#             */
/*   Updated: 2025/03/05 20:44:31 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*initialize_data(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		error_exit("Error:  allocating memory failed.\n", 1);
	data->env = NULL;
	data->cmd_list = NULL;
	data->cur_dir = NULL;
	data->status = 0;
	return (data);
}

t_cmd *create_cmd(void)
{
    t_cmd *cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return NULL;
    cmd->command = NULL;          // Comando vacío al principio
    cmd->args = NULL;             // Argumentos vacíos
    cmd->input_file = NULL;       // Sin archivo de entrada
    cmd->output_file = NULL;      // Sin archivo de salida
    cmd->append_output = 0;       // No hace append a la salida
    cmd->pipe = false;            // No hay tubería por defecto
    cmd->error_redirect = 0;      // Sin redirección de errores
    cmd->heredoc = false;         // No se maneja heredoc
    cmd->next = NULL;             // El siguiente comando es NULL al principio
    return cmd;
}
