/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonctions_lists.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:05:06 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/02/15 17:48:28 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	ft_lstadd_back_ps(t_nb **lst, t_nb *new)
{
	t_nb	*ptr;

	if (lst == NULL || new == NULL)
	{
		ft_printf("Pointer NULL in ft_lstadd_back_ps");
		return ;
	}
	ptr = *lst;
	if (lst != NULL)
	{
		if (*lst != NULL)
		{
			while (ptr->next != NULL)
			{
				ptr = ptr->next;
			}
			ptr->next = new;
		}
		else
			*lst = new;
	}
}

void	ft_lstclear_ps(t_nb **lst)
{
	t_nb	*temp;

	if (!lst || !*lst)
		return ;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		free (*lst);
		*lst = temp;
	}
	*lst = NULL;
}

int	ft_nb_of_list(t_nb *stack_a)
{
	int	count;

	count = 0;
	while (stack_a != NULL)
	{
		count++;
		stack_a = stack_a->next;
	}
	return (count);
}
