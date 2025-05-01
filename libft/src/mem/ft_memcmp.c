/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <mmarinov@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:15:55 by mmarinov          #+#    #+#             */
/*   Updated: 2024/06/27 14:07:13 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;
	size_t			iter;

	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	iter = 0;
	while (iter < n)
	{
		if (ptr1[iter] != ptr2[iter])
		{
			return (ptr1[iter] - ptr2[iter]);
		}
		iter++;
	}
	return (0);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*string1 = "Gralada all the world.";
	char	*string2 = "We are the world.";
	size_t	num = 10;
	int		result = ft_memcmp(string1, string2, num);

	if (result < 0)
	{
		printf("The first block of memory is smaller.\n");
	}
	else if (result > 0)
	{
		printf("The first block of memory is greater.\n");
	}
	else
	{
		printf("The blocks of memory are equal.\n");
	}
	printf("The result of FT_MEMCMP: %d\n", result);
	return (0);
}*/
