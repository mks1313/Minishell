/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:29:55 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/19 14:26:02 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Si no hay argumento, cambiar al directorio home
// Ahora funciona con t_env
// Si hay un argumento, intentar cambiar al directorio indicado
// Si no puede cambiar de directorio

static void	change_environment_pwd(t_env *env, char	*home)
{
	t_env	*copy;
	char	*old_pwd;

	copy = env;
	old_pwd = NULL;
	ft_printf(GREEN "%s\n" RES, home);
	change_env_variable(env, "OLDPWD", get_env_variable_value(env, "PWD"));
	change_env_variable(env, "PWD", home);
	while (copy->next != NULL)
	{
		if (ft_strcmp(copy->key, "OLDPWD") == 0)
			old_pwd = copy->value;
		copy = copy->next;
	}
	copy = env;
	while (copy->next != NULL)
	{
		if (ft_strcmp(copy->key, "PWD") == 0)
			copy->value = home;
		copy = copy->next;
	}
	(void)old_pwd;
}

// TODO: REVISAR LOS FALLOS DE CHDIR
void	ft_cd(t_cmd *cmd, t_shell *shell)
{
	char	*target_dir;
	char	*home;

	if (!cmd->args[1])
	{
		home = ft_getenv("HOME", shell->env);
		if (home)
		{
			if (chdir(home) == -1)
				perror("minishell: cd");
			else
				change_environment_pwd(shell->env, home);
		}
		else
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	}
	else
	{
		target_dir = cmd->args[1];
		if (chdir(target_dir) == -1)
			perror("minishell: cd");
		else
			change_environment_pwd(shell->env, target_dir);
	}
}
