/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:14:32 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/05 19:27:26 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Función para encontrar una variable de entorno*/
t_env	*find_env(t_env *env_list, const char *key)
{
	while (env_list)
	{
		if (strcmp(env_list->key, key) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

/* Función para agregar o actualizar una variable de entorno
 */
void	set_env(t_env **env_list, const char *key, const char *value)
{
	t_env	*var;
	t_env	*new_var;

	var = find_env(*env_list, key);
	if (var)
	{
		// Si la variable existe, actualizamos su valor
		free(var->value);
		var->value = strdup(value);
	}
	else
	{
		// Si no existe, creamos una nueva variable
		new_var = malloc(sizeof(t_env));
		new_var->key = strdup(key);
		if (new_var->value == value)
			ft_strdup(value);
		new_var->next = *env_list;
		*env_list = new_var;
	}
}

// Función principal de export
/*
void	ft_export(t_env **env_list, t_tkn *tokens)
{
	t_env	*var;
	t_tkn	*current;
	t_env	*env;
	char	*key;
	char	*value;
	char	*new_value;

	current = tokens->next;// Nos saltamos el "export"
	if (!current)
	{
		// Si nohay tokens despues d export, podemos imprimir las var de entorno
		env = *env_list;
		while (env)
		{
			ft_printf("%s", env->key);
			if (env->value)
				printf("=%s", env->value);
			ft_printf("\n");
			env = env->next;
		}
		return ;
	}
	while (current)
	{
		if (strchr(current->value, '='))
		{
			// Caso: export VAR=VALUE
			key = ft_strtok(current->value, "=");
			value = ft_strtok(NULL, "=");
			set_env(env_list, key, value);
		}
		else if (ft_strchr(current->value, '+')
			&& ft_strchr(current->value, '='))
		{
			// Caso: export VAR+=VALUE
			key = ft_strtok(current->value, "+=");
			value = ft_strtok(NULL, "+=");
			var = find_env(*env_list, key);
			if (var)
			{
				// Si la variable ya existe, agregamos el nuevo valor
				new_value = malloc(strlen(var->value) + strlen(value) + 1);
				ft_strcpy(new_value, var->value);
				ft_strcat(new_value, value);
				free(var->value);
				var->value = new_value;
			}
			else
			{
				// Si no existe, simple lo agregamos como una nueva variable
				set_env(env_list, key, value);
			}
		}
		current = current->next;
	}
}*/
