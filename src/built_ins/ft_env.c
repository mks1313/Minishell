/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 15:37:35 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/06 15:56:22 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * create_env_node - Crea un nuevo nodo del entorno con clave y valor
 * @env_str: String de entorno a partir del cual extraer clave y valor
 * 
 * Return: Nodo creado o NULL en caso de error
 */
t_env	*create_env_node(char *env_str)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = safe_strdup(ft_strtok(env_str, "="));
	if (!new_node->key || new_node->key[0] == '\0')
		return (free(new_node), NULL);
	new_node->value = safe_strdup(ft_strtok(NULL, "="));
	if (!new_node->value)
		return (free(new_node->key), free(new_node), NULL);
	new_node->next = NULL;
	return (new_node);
}

/**
 * add_env_node - Añade un nodo de entorno a la lista enlazada
 * @head: Puntero a la lista enlazada
 * @new_node: Nodo que se va a añadir
 */
void	add_env_node(t_env **head, t_env *new_node)
{
	t_env	*current;

	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}

/**
 * convert_env - Convierte el array envp en una lista enlazada de t_env
 * @envp: Array de strings de entorno (key=value)
 * 
 * Return: Lista enlazada de entorno o NULL en caso de error
 */
t_env	*convert_env(char **envp)
{
	t_env	*head;
	t_env	*new_node;
	int		i;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = create_env_node(envp[i]);
		if (!new_node)
			return (NULL);
		add_env_node(&head, new_node);
		i++;
	}
	return (head);
}

void	ft_env(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		ft_printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}
