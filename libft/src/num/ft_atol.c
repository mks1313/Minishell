/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:38:37 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/02 16:03:37 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	parse_sign(const char **s)
{
	int	sign;

	sign = 1;
	while (**s == 32 || (**s >= 9 && **s <= 13))
		(*s)++;
	if (**s == '-' || **s == '+')
	{
		if (**s == '-')
			sign = -1;
		(*s)++;
	}
	return (sign);
}

long	ft_atol(const char *s)
{
	int		sign;
	long	res;

	res = 0;
	sign = parse_sign(&s);
	while (ft_isdigit(*s))
	{
		if (res > (LONG_MAX - (*s - '0')) / 10)
		{
			if (sign == 1)
				return (LONG_MAX);
			else
				return (LONG_MIN);
		}
		res = res * 10 + (*s - '0');
		s++;
	}
	return (res * sign);
}
