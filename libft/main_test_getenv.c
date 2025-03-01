/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 11:39:52 by mmarinov          #+#    #+#             */
/*   Updated: 2025/03/01 11:53:53 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	main(int argc, char *argv[], char *envp[])
{
	if (argc != 2)
		return (ft_printf("ONLY TWO ARGS: %s VARIABLE\n", argv[0]));
	ft_printf("VALOR: %s\n", ft_getenv(argv[1], envp));
	if (ft_getenv(argv[1], envp))
		ft_printf("LEN: %i\n",ft_strlen(ft_getenv(argv[1], envp)));
}
