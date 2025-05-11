/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:06:36 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/08 19:34:29 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * init_shell - Initializes the shell structure
 * @shell_ptr: Pointer to the shell structure pointer
 *
 * Return: 0 on success, 1 on failure
 */
int	init_shell(t_shell **shell_ptr)
{
	*shell_ptr = (t_shell *)ft_calloc(1, sizeof(t_shell));
	return (*shell_ptr == NULL);
}