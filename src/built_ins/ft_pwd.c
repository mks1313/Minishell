/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:15:16 by mmarinov          #+#    #+#             */
/*   Updated: 2025/03/29 14:00:13 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * ft_pwd - Imprime el directorio de trabajo actual
 */
// TODO: remove red color
void	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_putstr_fd(RED, 1);
		ft_putendl_fd(cwd, 1);
		ft_putstr_fd(RES, 1);
		free(cwd);
	}
	else
		perror("minishell: pwd");
}