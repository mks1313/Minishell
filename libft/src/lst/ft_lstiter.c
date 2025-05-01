/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:05:19 by mmarinov          #+#    #+#             */
/*   Updated: 2024/07/17 19:18:02 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
#include <stdio.h>

void print_content(void *content)
{
	printf("%s\n", (char *)content);
}

int main(void)
{
	// Create content dynamically
	char *content1 = ft_strdup("Node 1");
	char *content2 = ft_strdup("Node 2");
	char *content3 = ft_strdup("Node 3");

	// Create nodes
	t_list *node1 = ft_lstnew((void *)content1);
	t_list *node2 = ft_lstnew((void *)content2);
	t_list *node3 = ft_lstnew((void *)content3);

	if (!node1 || !node2 || !node3)
	{
		printf("Error creating nodes.\n");
		return (1);
	}
	// Link nodes
	node1->next = node2;
	node2->next = node3;
	// Create the list
	t_list *list = node1;
	// Iterate over the list and print its content
	ft_lstiter(list, print_content);
	// Clean memory (optional)
	ft_lstclear(&list, free);
	return (0);
}*/
