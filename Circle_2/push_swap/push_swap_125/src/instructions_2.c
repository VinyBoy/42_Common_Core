/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:07:51 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/02/06 18:29:08 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	reverse_rotate_r(t_nb **stack_a, t_nb **stack_b, int indice)
{
	reverse_rotate(*&stack_a, 2);
	reverse_rotate(*&stack_b, 2);
	if (indice == 2)
		ft_printf("rrr\n");
}

void	push_a(t_nb **stack_a, t_nb **stack_b)
{
	t_nb	*temp;

	if (!(*stack_b))
		return ;
	temp = (*stack_b);
	(*stack_b) = (*stack_b)->next;
	temp->next = (*stack_a);
	(*stack_a) = temp;
	ft_printf("pa\n");
}

void	push_b(t_nb **stack_a, t_nb **stack_b)
{
	t_nb	*temp;

	if (!(*stack_a))
		return ;
	temp = (*stack_a);
	(*stack_a) = (*stack_a)->next;
	temp->next = (*stack_b);
	(*stack_b) = temp;
	ft_printf("pb\n");
}
