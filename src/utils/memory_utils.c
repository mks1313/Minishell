/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:33:05 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/28 20:39:25 by mmarinov         ###   ########.fr       */
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

/**
 * This function is used to exit the program cleanly. It frees all allocated
 * memory associated with the shell and clears the history of the readline
 * library. The function returns the given status as the exit status.
 * shell The shell structure containing the data to be freed.
 * status The exit status to return.
 * return The provided exit status.
 */
int	clean_exit(t_shell *shell, int status)
{
	return (free_data(shell), rl_clear_history(), status);
}

/**
 * This function frees a linked list of token parts (t_tkn_part). It iterates
 * through each element of the list, frees the associated value and the part
 * structure itself, and moves to the next element. The list is freed in
 * order until all elements are cleaned up.
 */
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
