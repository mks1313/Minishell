/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:12:14 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/28 13:07:18 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Counts the number of environment variables in the linked list.
 * Returns the total number of elements.
 */
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

/**
 * Joins three strings into a newly allocated result: res = s1 + s2 + s3.
 **/
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

/**
 * Fills an array with environment variables in "KEY=VALUE" format.
 * Returns 1 on success, 0 on allocation failure.
 */
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

/**
 * Converts the environment list to an array of strings "KEY=VALUE".
 * Returns NULL on allocation error.
 **/
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

/**
 * Uses stat to check if the given path is a directory.
 * Returns 1 if dir, -1 if error, 0 otherwise.
 **/
int	is_directory(const char *path)
{
	struct stat	info;

	if (stat(path, &info) != 0)
		return (-1);
	if (S_ISDIR(info.st_mode))
		return (1);
	return (0);
}
