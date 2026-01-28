/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:16:41 by vnieto-j          #+#    #+#             */
/*   Updated: 2024/11/20 13:31:10 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst != NULL)
	{
		while (lst->next != NULL)
			lst = lst->next;
		return (lst);
	}
	else
		return (NULL);
}

// #include <stdio.h>

// int main(void)
// {
// 	t_list node3 = {"Node3", NULL};
// 	t_list node2 = {"Node2", &node3};
// 	t_list node1 = {"Node1", &node2};
// 	t_list *new_node;
// 	new_node = ft_lstlast(&node1);
// 	printf("Content of last node = %s\n", (char *)new_node->content);
// 	printf("Adresse of next node of the last = %p\n", new_node->next);
// 	return (0);
// }