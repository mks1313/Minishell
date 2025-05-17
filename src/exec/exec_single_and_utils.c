/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_and_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:12:14 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/17 13:32:36 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * clean_array - Frees all the memory of a NULL-terminated string array
 * @array: The array to free
 *
 * This function frees each string in the array and then the array itself.
 * If the array is NULL, it does nothing.
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

static int	fill_env_array(char **env_array, t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env_array[i] = ft_strjoin3(env->key, "=", env->value);
		if (!env_array[i])
			return (clean_array(env_array), 0);
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
