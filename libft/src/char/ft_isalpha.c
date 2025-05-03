/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <mmarinov@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:53:28 by mmarinov          #+#    #+#             */
/*   Updated: 2025/02/26 15:02:54 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <ctype.h>
#include "../../includes/libft.h"

int	ft_isalpha(int c)
{
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}
/*
int	main()
{
	char	c;
	char	b;

	c = 65;
	b = 92;
	printf("My function, with letter %d \n", ft_isalpha(c));
	printf("Oficcial, with letter %d \n", isalpha(c));
	printf("My funct, with no letter %d \n", ft_isalpha(b));
	printf("Official funct, with no letter %d \n", isalpha(b));
	return (0);
}
*/
