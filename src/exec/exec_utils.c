/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:12:14 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/25 11:03:12 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * clean_array - Libera toda la memoria de un array de strings terminado en NULL
 * @array: El array a liberar
 *
 * Esta función libera cada string en el array y luego el propio array.
 * Es segura para usar con NULL.
 */
void	clean_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*res;

	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		s2 = ft_strdup("");
	if (!s3)
		s3 = ft_strdup("");
	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, s3);
	free(tmp);
	if (!res)
		return (NULL);
	return (res);
}

char	**env_to_array(t_env *env)
{
	int		i;
	int		count;
	char	**env_array;
	t_env	*curr;

	count = 0;
	curr = env;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
	env_array = (char **)malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	i = 0;
	curr = env;
	while (curr)
	{
		env_array[i] = ft_strjoin3(curr->key, "=", curr->value);
		if (!env_array[i])
		{
			clean_array(env_array);
			return (NULL);
		}
		i++;
		curr = curr->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
