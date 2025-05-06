/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:29:55 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/06 18:06:28 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Función que actualiza el valor de una variable de entorno
static void	update_env_variable(t_env *env, char *key, char *value)
{
	t_env	*copy;

	copy = env;
	while (copy != NULL)
	{
		if (ft_strcmp(copy->key, key) == 0)
		{
			if (copy->value != NULL)
				free(copy->value);
			copy->value = ft_strdup(value);
			return ;
		}
		copy = copy->next;
	}
}

// Actualiza las variables OLDWD y PWD en el entorno
static void	update_pwd_variables(t_env *env, char *old_pwd_val, char *new_path)
{
	char	*old_pwd_dup;
	char	*new_pwd_dup;

	old_pwd_dup = dup_if_needed(old_pwd_val);
	new_pwd_dup = ft_strdup(new_path);
	if (new_pwd_dup == NULL)
	{
		free(old_pwd_dup);
		return ;
	}
	update_env_variable(env, "OLDPWD", old_pwd_dup);
	update_env_variable(env, "PWD", new_pwd_dup);
	free(old_pwd_dup);
	free(new_pwd_dup);
}

void	change_environment_pwd(t_env *env, char *new_path)
{
	char	*old_pwd_val;

	old_pwd_val = ft_getenv("PWD", env);
	update_pwd_variables(env, old_pwd_val, new_path);
}

int	ft_cd(t_cmd *cmd, t_shell *shell)
{
	char	*target_dir;
	char	*home;

	if (!cmd->args[1])
	{
		home = ft_getenv("HOME", shell->env);
		if (!home)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			shell->exit_status = 1;
			return (1);
		}
		if (chdir(home) == -1)
		{
			perror("minishell: cd");
			shell->exit_status = 1;
			return (1);
		}
		change_environment_pwd(shell->env, home);
		shell->exit_status = 0;
	}
	else
	{
		target_dir = cmd->args[1];
		if (chdir(target_dir) == -1)
		{
			perror("minishell: cd");
			shell->exit_status = 1;
			return (1);
		}
		change_environment_pwd(shell->env, target_dir);
		shell->exit_status = 0;
	}
	return (0);
}
