/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:06:36 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/09 17:52:37 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
	Initializes the shell structure.
	@param shell_ptr: Pointer to the shell structure pointer.
	@return 0 on success, 1 on failure.
 */
int	init_shell(t_shell **shell_ptr)
{
	*shell_ptr = (t_shell *)malloc(sizeof(t_shell));
	if (!*shell_ptr)
		return (1);
	ft_memset(*shell_ptr, 0, sizeof(t_shell));
	return (0);
}
/*
t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->redirects = NULL;
	cmd->next = NULL;
	return (cmd);
}*/
