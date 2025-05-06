/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:18:41 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/05 15:49:34 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(const char *key)
{
	int	i;

	if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_identifier_export(const char *key)
{
	if (!is_valid_identifier(key))
	{
		ft_printf("export; `%s': not a valid identifier\n", key);
		return (0);
	}
	return (1);
}

void	append_to_env(t_env **env, const char *key, const char *value)
{
	t_env	*var;
	char	*new_val;

	var = find_env(*env, key);
	if (var && var->value)
	{
		new_val = malloc(ft_strlen(var->value) + ft_strlen(value) + 1);
		if (!new_val)
			error_exit("MALLOC FAILED!", 1);
		ft_strcpy(new_val, var->value);
		ft_strcat(new_val, value);
		free(var->value);
		var->value = new_val;
	}
	else
		update_or_append_env(env, key, value);
}

t_env	*find_env(t_env *env_list, const char *key)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, key) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

void	update_or_append_env(t_env **env, const char *key, const char *value)
{
	t_env	*var;
	t_env	*new;

	var = find_env(*env, key);
	if (var)
	{
		free(var->value);
		if (value)
			var->value = ft_strdup(value);
		else
			var->value = NULL;
	}
	else
	{
		new = malloc(sizeof(t_env));
		if (!new)
			error_exit("MALLOC FAILED!", 1);
		new->key = ft_strdup(key);
		if (value)
			new->value = ft_strdup(value);
		else
			new->value = NULL;
		new->next = *env;
		*env = new;
	}
}

void	print_export_list(t_env *env)
{
	while (env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
}
