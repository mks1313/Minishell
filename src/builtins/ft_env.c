/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 15:37:35 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/19 15:17:26 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * create_env_node - Crea un nuevo nodo del entorno con clave y valor
 * @env_str: String de entorno a partir del cual extraer clave y valor
 * 
 * Return: Nodo creado o NULL en caso de error
 */
t_env	*create_env_kv(const char *key, const char *value)
{
	t_env	*new_node;

	if (!key || !value)
		return (NULL);
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	if (!new_node->key || !new_node->value)
	{
		free(new_node->key);
		free(new_node->value);
		free(new_node);
		return (NULL);
	}
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

int	ft_env(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (current->value)
			ft_printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (0);
}

/**
 * setup_environment - Initializes the environment for the shell
 * @shell: Main shell structure
 * @envp: System environment array
 * 
 * Return: 0 on success, 1 on failure
 */
int	setup_environment(t_shell *shell, char **envp)
{
	t_env	*env_list;
	t_env	*new_node;
	char	*key;
	char	*value;
	int		i;

	env_list = NULL;
	i = 0;
	if (!shell || !envp)
		return (1);
	while (envp[i])
	{
		key = ft_strtok(envp[i], "=");
		value = ft_strtok(NULL, "=");
		if (!key || !value)
			return (free_env_list(env_list), 1);
		new_node = create_env_kv(key, value);
		if (!new_node)
			return (free_env_list(env_list), 1);
		add_env_node(&env_list, new_node);
		i++;
	}
	shell->env = env_list;
	return (0);
}
