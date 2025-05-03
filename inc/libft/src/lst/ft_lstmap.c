/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 10:32:40 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/03 19:03:48 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;

	if (!lst || !f)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_node = ft_lstnew(f(lst->content));
		if (!new_node)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
/*
#include <stdio.h>

// Transformation function for tests.
void *double_content(void *content)
{
    int *new_content = (int *)malloc(sizeof(int));
    if (new_content)
        *new_content = *(int *)content * 2;
    return new_content;
}

// Deletion function for tests.
void delete_content(void *content)
{
    free(content);
}

// Function to print a list of integers.
void print_list(t_list *lst)
{
    while (lst)
    {
        printf("%d -> ", *(int *)(lst->content));
        lst = lst->next;
    }
    printf("NULL\n");
}

int	main(void)
{
    // Create a simple list of integers.
    int a = 1, b = 2, c = 3;
    t_list *lst = ft_lstnew(&a);
    ft_lstadd_back(&lst, ft_lstnew(&b));
    ft_lstadd_back(&lst, ft_lstnew(&c));

    // Print the original list.
    printf("Original list:\n");
    print_list(lst);

    // Create a new list applying the double_content function.
    t_list *new_lst = ft_lstmap(lst, double_content, delete_content);

    // Print the new list.
    printf("New list (duplicated content):\n");
    print_list(new_lst);

    // Clean memory.
    ft_lstclear(&new_lst, delete_content);
    // No needs to delete the original content, it's static.
    ft_lstclear(&lst, NULL); 

    return 0;
}*/
