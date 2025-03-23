/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:14:34 by meghribe          #+#    #+#             */
/*   Updated: 2025/03/23 17:48:58 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(const char *msg, int exit_code)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd(RES, 2);
	exit(exit_code);
}

