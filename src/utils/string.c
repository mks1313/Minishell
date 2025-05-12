/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:00:36 by meghribe          #+#    #+#             */
/*   Updated: 2025/05/12 16:28:01 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Duplicates the string with null verification
 * 
 * This function checks the string before try to duplicate. To avoid segfaults
 * 
 * @param s The string to duplicate
 * @return The copied string or empty string if its NULL
 */

char	*safe_strdup(const char *s)
{
	if (!s)
		return (ft_strdup(""));
	return (ft_strdup(s));
}
