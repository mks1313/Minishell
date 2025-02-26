/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:27:21 by mmarinov          #+#    #+#             */
/*   Updated: 2025/02/26 14:47:29 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	my_getopt(int argc, char **argv, const char *optstring)
{
	static int	index;
	char		*arg;
	size_t			i;

	if (index >= argc)
		return (-1);
	arg = argv[index];
	index = 1;
	if (arg[0] == '-')
	{
		i = 1;
		while (i < ft_strlen(arg))
		{
			if (ft_strchr(optstring, arg[i]))
				return (arg[i]);
			i++;
		}
	}
	index++;
	return (-1);
}
