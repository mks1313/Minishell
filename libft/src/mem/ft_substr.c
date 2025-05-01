/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <mmarinov@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:51:38 by mmarinov          #+#    #+#             */
/*   Updated: 2024/07/09 19:52:34 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	substring = (char *)ft_calloc((len + 1), sizeof(char));
	if (substring == NULL)
		return (NULL);
	while (len--)
		substring[len] = s[((size_t)start) + len];
	return (substring);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*origin = "";
	unsigned int	index = 29;
	size_t	length = 4;
	char	*result = ft_substr(origin, index, length);

	if (result == NULL)
	{
		printf("The function ft_substr returns NULL.\n");
	}
	else if (result[0] == '\0')
	{
		printf("The starting index is greater than the length of the string.\n");
		free(result);
	}
	else
	{
		printf("The result of the copy of ft_substr is: %s.\n", result);
		free(result);
	}
	return (0);
}*/
