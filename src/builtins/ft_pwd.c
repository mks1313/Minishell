/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:15:16 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/06 17:17:23 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_putstr_fd(RED, 1);
		ft_putendl_fd(cwd, 1);
		ft_putstr_fd(RES, 1);
		free(cwd);
		return (0);
	}
	else
	{
		perror("minishell: pwd");
		return (1);
	}
}
