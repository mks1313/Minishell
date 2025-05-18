/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <mmarinov@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:27:05 by mmarinov          #+#    #+#             */
/*   Updated: 2024/07/11 18:27:47 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*copy;

	copy = (char *)malloc(ft_strlen(s) + 1);
	if (!copy)
		return (NULL);
	ft_strlcpy(copy, s, (ft_strlen(s) + 1));
	return (copy);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*origin = "Hello, world!";
	char	*result = ft_strdup(origin);
	printf("copied string %s\n", result);
	printf("memory address is: %p", result);
	printf("memory address is: %p", origin); 
	return (0);
}*/
