/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:16:41 by vnieto-j          #+#    #+#             */
/*   Updated: 2024/11/20 13:22:14 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ptr;

	ptr = malloc(sizeof(t_list));
	if (!ptr)
		return (NULL);
	ptr->content = content;
	ptr->next = NULL;
	return (ptr);
}

// #include <stdio.h>

// int main(void)
// {
// 	char 	*content;
// 	t_list	*new_node;

// 	content = "Hello my name is";
// 	new_node = ft_lstnew(content);
// 	if (!new_node)
// 	{
// 		printf("Bad allocation\n");
// 		return (1);
// 	}	
// 	printf("content of new node = %s\n", (char *)new_node->content);
// 	printf("adresse of next node = %p\n", new_node->next);
// 	return (0);
// }