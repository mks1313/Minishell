/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <mmarinov@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:08:31 by mmarinov          #+#    #+#             */
/*   Updated: 2025/03/01 11:42:38 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*str = "Hello, World";
	int		f = 'o';
	char	*result = ft_strchr(str, f);

	if (result != NULL)
	{
		printf("Caracer encontrado %s\n", result);
	}
	else
	{
		printf("Caracter no encontrado\n");
	}
	return (0);
}*/
