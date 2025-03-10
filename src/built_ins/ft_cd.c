/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:29:55 by mmarinov          #+#    #+#             */
/*   Updated: 2025/03/10 18:26:36 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_tkn *tokens, t_shell *shell)
{
	if (!tokens || !tokens->next)  // Si no hay argumento, cambiar al directorio home
	{
		char *home = ft_getenv("HOME", shell->env);  // Ahora funciona con t_env
		if (home)
			chdir(home);
		else
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	}
	else  // Si hay un argumento, intentar cambiar al directorio indicado
	{
		if (chdir(tokens->next->value) == -1)  // Si no puede cambiar de directorio
		{
			perror("minishell: cd");
		}
	}
}
