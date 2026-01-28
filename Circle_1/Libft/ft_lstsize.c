/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:16:41 by vnieto-j          #+#    #+#             */
/*   Updated: 2024/11/20 13:11:48 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

// #include <stdio.h>

// int	main(void)
// {
// 	int	count;

// 	count = 0;
// 	t_list node3 = {"Node3", NULL};
// 	t_list node2 = {"Node2", &node3};
// 	t_list node1 = {"Node1", &node2};
// 	count = ft_lstsize(&node1);
// 	printf("Dans ma liste i y a : %d noeuds", count);
// 	return (0);
// }