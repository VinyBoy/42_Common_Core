/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:15:20 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/06/12 17:26:31 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	reverse_rotate_r(t_nb **stack_a, t_nb **stack_b, char c)
{
	reverse_rotate(*&stack_a, c);
	reverse_rotate(*&stack_b, c);
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
