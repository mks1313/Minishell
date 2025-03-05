/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:14:34 by meghribe          #+#    #+#             */
/*   Updated: 2025/03/05 20:49:12 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(const char *message, int exit_code)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd((char *)message, 2);
	ft_putstr_fd(RESET, 2);
	exit(exit_code);
}

void	del(void *content)
{
	free(content);
}

void	free_data(t_data *data)
{
	// Liberar la lista de variables de entorno
	t_env	*env;
	t_env	*tmp;
	t_cmd	*cmd_list;
	t_cmd *cmd_tmp;

	env = data->env;
	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
	// Liberar la lista de comandos
	cmd_list = data->cmd_list;
	while (cmd_list)
	{
		cmd_tmp = cmd_list->next;
		free(cmd_list->command);
		// Si args es una lista dinámica, liberar cada elemento también
		if (cmd_list->args)
		{
			for (int i = 0; cmd_list->args[i]; i++)
				free(cmd_list->args[i]);
			free(cmd_list->args);
		}
		free(cmd_list->input_file);
		free(cmd_list->output_file);
		free(cmd_list);
		cmd_list = cmd_tmp;
	}

	// Liberar el directorio actual y la estructura de datos
	free(data->cur_dir);
	free(data);
}
