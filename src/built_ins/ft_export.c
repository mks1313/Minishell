/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:14:32 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/13 14:25:48 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*find_env(t_env *env_list, const char *key)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, key) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

static int	is_valid_identifier(const char *key)
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

static void	append_to_env(t_env **env, const char *key, const char *value)
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

static void	export_single_arg(t_env **env, const char *arg, int *status)
{
	char	*key;
	char	*value;
	char	*plus;

	key = NULL;
	value = NULL;
	plus = ft_strnstr(arg, "+=", ft_strlen(arg));
	if (plus)
	{
		key = ft_substr(arg, 0, plus - arg);
		value = ft_strdup(plus + 2);
		if (!is_valid_identifier(key))
		{
			dprintf(2, "export: `%s': not a valid identifier\n", arg);
			*status = 1;
		}
		else
			append_to_env(env, key, value);
	}
	else if (ft_strchr(arg, '='))
	{
		key = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
		value = ft_strdup(ft_strchr(arg, '=') + 1);
		if (!is_valid_identifier(key))
		{
			dprintf(2, "export: `%s': not a valid identifier\n", arg);
			*status = 1;
		}
		else
			update_or_append_env(env, key, value);
	}
	else
	{
		if (!is_valid_identifier(arg))
		{
			dprintf(2, "export: `%s': not a valid identifier\n", arg);
			*status = 1;
		}
		else if (!find_env(*env, arg))
			update_or_append_env(env, arg, NULL);
	}
	free(key);
	free(value);
}

void	ft_export(t_env **env, t_cmd *cmd)
{
	int	status;
	int	i;

	status = 0;
	i = 1;
	if (!cmd->args[1])
		return ;
	while (cmd->args[i])
		export_single_arg(env, cmd->args[i++], &status);
}
