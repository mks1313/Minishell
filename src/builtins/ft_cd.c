/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:29:55 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/07 15:16:20 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Update value of var in env
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

// Update vars OLDWD y PWD in ENV
static void	update_pwd_variables(t_env *env, char *old_pwd_val, char *new_path)
{
	char	*old_pwd_dup;
	char	*new_pwd_dup;

	if (!old_pwd_val)
		old_pwd_dup = NULL;
	else
		old_pwd_dup = ft_strdup(old_pwd_val);
	new_pwd_dup = ft_strdup(new_path);
	if (new_pwd_dup == NULL)
		return ((void)free(old_pwd_dup));
	update_env_variable(env, "OLDPWD", old_pwd_dup);
	update_env_variable(env, "PWD", new_pwd_dup);
	free(old_pwd_dup);
	free(new_pwd_dup);
}

void	change_environment_pwd(t_env *env, char *new_path)
{
	update_pwd_variables(env, ft_getenv("PWD", env), new_path);
}

static int	cd_to_home(t_shell *shell)
{
	char	*home;
	char	cwd[PATH_MAX];

	home = ft_getenv("HOME", shell->env);
	shell->exit_status = 1;
	if (!home)
		return (ft_putstr_fd(ERR_CD_NOT_SET, 2), 1);
	if (chdir(home) == -1)
		return (perror(ERR_CD), 1);
	if (!getcwd(cwd, sizeof(cwd)))
		ft_putstr_fd(ERR_RETRIEVING, 2);
	else
		change_environment_pwd(shell->env, home);
	shell->exit_status = 0;
	return (0);
}

int	ft_cd(t_cmd *cmd, t_shell *shell)
{
	char	*target_dir;
	char	cwd[PATH_MAX];

	if (!cmd->args[1])
		return (cd_to_home(shell));
	target_dir = cmd->args[1];
	if (chdir(target_dir) == -1)
	{
		perror("minishell: cd");
		shell->exit_status = 1;
		return (1);
	}
	if (!getcwd(cwd, sizeof(cwd)))
		ft_putstr_fd("minishell: cd: error retrieving current directory: \
				getcwd: cannot access parent directories: \
				No such file or directory\n", 2);
	else
		change_environment_pwd(shell->env, target_dir);
	shell->exit_status = 0;
	return (0);
}
