/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 15:37:35 by mmarinov          #+#    #+#             */
/*   Updated: 2025/03/05 18:54:09 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			return (NULL);
		new_node->key = ft_strdup(ft_strtok_quotes(envp[i], "="));
		new_node->value = ft_strdup(ft_strtok_quotes(NULL, "="));
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
