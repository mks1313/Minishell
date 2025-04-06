/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:29:55 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/06 16:23:02 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Si no hay argumento, cambiar al directorio home
// Ahora funciona con t_env
// Si hay un argumento, intentar cambiar al directorio indicado
// Si no puede cambiar de directorio
//

static void	ft_print_list(t_env *env)
{
	t_env *copy;

	copy = env;
	while (copy->next != NULL)
	{
		ft_printf(RED"%s=%s\n"RES, copy->key, copy->value);
		copy = copy->next;
	}
}

static void	change_environment_pwd(t_env *env, char	*home)
{
	t_env *copy;
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
void	ft_cd(t_tkn *tokens, t_shell *shell)
{
	char	*home;
	printf("XD");

	ft_print_list(shell->env);
	return ;
	if (!tokens || !tokens->next)
	{
		home = ft_getenv("HOME", shell->env);
		if (home)
		{
			change_environment_pwd(shell->env, home);
			chdir(home);
		}
		else
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	}
	else
	{
		if (chdir(tokens->next->value) == -1)
			perror("minishell: cd");
		change_environment_pwd(shell->env, tokens->next->value);
	}
}
