/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:19:24 by mmarinov          #+#    #+#             */
/*   Updated: 2024/07/15 15:46:30 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
/*
#include <stdio.h>

int	main(void)
{
	t_list	*list = ft_lstnew("hello!");
	ft_lstadd_front(&list,ft_lstnew("world!"));
	ft_lstadd_front(&list, ft_lstnew("hola"));

	int	num = ft_lstsize(list);
	printf("The total number of lists is: %d\n", num);
	while (list)
	{
	printf("%s", (char *)list->content);
	list = list->next;
	}
	return (0);
}*/
