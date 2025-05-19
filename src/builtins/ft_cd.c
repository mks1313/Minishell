/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:29:55 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/19 16:27:43 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

// Update value of var in env
static void	append_new_env_node(t_env **env, t_env *new)
{
	t_env	*curr;

	if (!*env)
		*env = new;
	else
	{
		curr = *env;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

static void	update_env_variable(t_env **env, const char *key, const char *value)
{
	t_env	*curr;
	t_env	*new;

	if (!env || !key || !value)
		return ;
	curr = *env;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			free(curr->value);
			curr->value = ft_strdup(value);
			return ;
		}
		curr = curr->next;
	}
	new = create_env_kv(key, value);
	if (!new)
		return ;
	append_new_env_node(env, new);
}

// Update vars OLDPWD y PWD in ENV
static void	update_pwd_variables(t_env *env, char *old_pwd_val, char *new_path)
{
	char	*old_pwd_dup;
	char	*new_pwd_dup;

	old_pwd_dup = NULL;
	if (old_pwd_val)
		old_pwd_dup = ft_strdup(old_pwd_val);
	new_pwd_dup = ft_strdup(new_path);
	if (!new_pwd_dup)
	{
		if (old_pwd_dup)
			free(old_pwd_dup);
		return ;
	}
	if (old_pwd_dup)
		update_env_variable(&env, "OLDPWD", old_pwd_dup);
	update_env_variable(&env, "PWD", new_pwd_dup);
	free(old_pwd_dup);
	free(new_pwd_dup);
}

static int	cd_to_home(t_shell *shell)
{
	char	*home;
	char	cwd[PATH_MAX];

	home = ft_getenv("HOME", shell->env);
	shell->exit_status = 1;
	if (!home)
		return (ft_putstr_fd(ERR_CD_NOT_SET, STDERR_FILENO), 1);
	if (chdir(home) == -1)
		return (perror(ERR_CD_PREFIX), 1);
	if (!getcwd(cwd, sizeof(cwd)))
		ft_putstr_fd(ERR_CD_RETRIEVE, STDERR_FILENO);
	else
		update_pwd_variables(shell->env, ft_getenv("PWD", shell->env), cwd);
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
		perror(ERR_CD_PREFIX);
		shell->exit_status = 1;
		return (1);
	}
	if (!getcwd(cwd, sizeof(cwd)))
		ft_putstr_fd(ERR_CD_RETRIEVE, STDERR_FILENO);
	else
		update_pwd_variables(shell->env, ft_getenv("PWD", shell->env), cwd);
	shell->exit_status = 0;
	return (0);
}
