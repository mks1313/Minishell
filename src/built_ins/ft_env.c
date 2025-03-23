/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 15:37:35 by mmarinov          #+#    #+#             */
/*   Updated: 2025/03/23 14:14:40 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*convert_env(char **envp)
{
	t_env	*head;
	t_env	*new_node;
	t_env	*current;
	int		i;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (NULL);  // Si no se puede asignar memoria, devolver NULL
		new_node->key = ft_strdup(ft_strtok_quotes(envp[i], "="));
		if (!new_node->key || new_node->key[0] == '\0')  // Verificar si `key` es NULL o vacío
		{
			free(new_node);  // Liberar el nodo recién creado
			return (NULL);  // Devolver NULL
		}
		new_node->value = ft_strdup(ft_strtok_quotes(NULL, "="));
		if (!new_node->value)  // Si `ft_strdup` falla
		{
			free(new_node->key);  // Liberar la clave
			free(new_node);  // Liberar el nodo recién creado
			return (NULL);  // Devolver NULL
		}
		new_node->next = NULL;
		if (head == NULL)
			head = new_node;
		else
		{
			current = head;
			while (current->next)
				current = current->next;
			current->next = new_node;
		}
		i++;  // Avanzar al siguiente elemento en `envp`
	}
	return (head);  // Devolver la lista de variables de entorno
}

void	ft_env(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	//ft_printf("CURRENT AL PRINCIPIO: %p\n", current);
	//ft_printf("ENV AL PRINCIIPIO: %p\n", env_list);
	while (current)
	{
		ft_printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	//ft_printf("CURRENT AL FINAL: %p\n", current);
	//ft_printf("ENV AL FINAL: %p\n", env_list);
}

