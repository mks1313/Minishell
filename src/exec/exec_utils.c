/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:12:14 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/07 14:39:16 by mmarinov         ###   ########.fr       */
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

static int	count_env_vars(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

static int	fill_env_array(char **env_array, t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env_array[i] = ft_strjoin3(env->key, "=", env->value);
		if (!env_array[i])
		{
			clean_array(env_array);
			return (0);
		}
		i++;
		env = env->next;
	}
	env_array[i] = NULL;
	return (1);
}

char	**env_to_array(t_env *env)
{
	int		count;
	char	**env_array;

	count = count_env_vars(env);
	env_array = (char **)malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	if (!fill_env_array(env_array, env))
		return (NULL);
	return (env_array);
}
