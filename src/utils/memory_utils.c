/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:33:05 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/20 11:12:46 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * clean_array - Frees all the memory of a NULL-terminated string array
 * @array: The array to free
 *
 * This function frees each string in the array and then the array itself.
 * If the array is NULL, it does nothing.
 */
void	clean_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

int	clean_exit(t_shell *shell, int status)
{
	return (free_data(shell), rl_clear_history(), status);
}

void	ft_free_parts(t_tkn_part *parts)
{
	t_tkn_part	*tmp;

	while (parts)
	{
		tmp = parts->next;
		free(parts->value);
		free(parts);
		parts = tmp;
	}
}
