/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:14:32 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/06 17:23:37 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Process kye & value for the argument `+=`
static void	process_plus_equals(t_env **env, const char *arg, int *status)
{
	char	*key;
	char	*value;
	char	*plus;

	plus = ft_strnstr(arg, "+=", ft_strlen(arg));
	key = ft_substr(arg, 0, plus - arg);
	value = ft_strdup(plus + 2);
	if (is_valid_identifier_export(key))
		append_to_env(env, key, value);
	if (*status == 0)
		*status = 1;
	free(key);
	free(value);
}

// Procesa argument with `=`
static void	process_equals(t_env **env, const char *arg, int *status)
{
	char	*key;
	char	*value;

	key = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
	value = ft_strdup(ft_strchr(arg, '=') + 1);
	if (is_valid_identifier_export(key))
		update_or_append_env(env, key, value);
	if (*status == 0)
		*status = 1;
	free(key);
	free(value);
}

// Process simple arg without `=` ni `+=`
static void	process_simple_arg(t_env **env, const char *arg)
{
	if (is_valid_identifier_export(arg) && !find_env(*env, arg))
		update_or_append_env(env, arg, NULL);
}

// Principal function to export arg
static void	export_single_arg(t_env **env, const char *arg, int *status)
{
	if (ft_strnstr(arg, "+=", ft_strlen(arg)))
		process_plus_equals(env, arg, status);
	else if (ft_strchr(arg, '='))
		process_equals(env, arg, status);
	else
		process_simple_arg(env, arg);
}

int	ft_export(t_env **env, t_cmd *cmd)
{
	int	status;
	int	i;

	status = 0;
	i = 1;
	if (!cmd->args[1])
	{
		print_export_list(*env);
		return (1);
	}
	while (cmd->args[i])
		export_single_arg(env, cmd->args[i++], &status);
	return (0);
}
