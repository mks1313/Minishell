/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:33:05 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/14 14:16:47 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	return (free(s1), result);
}

char	*ft_strjoin_char(char *s, char c)
{
	char	*str;
	int		len;

	len = ft_strlen(s);
	str = malloc(len + 2);
	if (!str)
		return (NULL);
	ft_strcpy(str, s);
	str[len] = c;
	str[len + 1] = '\0';
	return (free(s), str);
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
