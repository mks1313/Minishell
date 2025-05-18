/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:43:35 by mmarinov          #+#    #+#             */
/*   Updated: 2025/03/23 17:36:41 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(const char *name, t_env *env)
{
	t_env	*curr;
	size_t	len;

	if (!name)
		return (NULL);
	len = ft_strlen(name);
	curr = env;
	while (curr)
	{
		if (ft_strncmp(curr->key, name, len) == 0 && curr->key[len] == '\0')
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}
