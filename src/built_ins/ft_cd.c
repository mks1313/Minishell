/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:29:55 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/05 19:26:14 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Si no hay argumento, cambiar al directorio home
// Ahora funciona con t_env
// Si hay un argumento, intentar cambiar al directorio indicado
// Si no puede cambiar de directorio
/*
void	ft_cd(t_tkn *tokens, t_shell *shell)
{
	char	*home;

	if (!tokens || !tokens->next)
	{
		home = ft_getenv("HOME", shell->env);
		if (home)
			chdir(home);
		else
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	}
	else
	{
		if (chdir(tokens->next->value) == -1)
			perror("minishell: cd");
	}
}*/
