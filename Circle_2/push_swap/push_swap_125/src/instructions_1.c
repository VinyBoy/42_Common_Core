/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:08:19 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/02/06 16:15:42 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	swap(t_nb **stack, int indice)
{
	t_nb	*temp;

	if (!*stack || !(*stack)->next)
		return ;
	temp = (*stack)->next;
	(*stack)->next = temp->next;
	temp->next = (*stack);
	(*stack) = temp;
	if (indice == 0)
		ft_printf("sa\n");
	if (indice == 1)
		ft_printf("sb\n");
}

void	swap_ss(t_nb **stack_a, t_nb **stack_b, int indice)
{
	swap(*&stack_a, 2);
	swap(*&stack_b, 2);
	if (indice == 2)
		ft_printf("ss\n");
}

void	rotate(t_nb **stack, int indice)
{
	t_nb	*temp;

	if (!*stack || !(*stack)->next)
		return ;
	temp = (*stack);
	(*stack) = (*stack)->next;
	temp->next = NULL;
	ft_lstadd_back_ps(stack, temp);
	if (indice == 0)
		ft_printf("ra\n");
	else if (indice == 1)
		ft_printf("rb\n");
}

void	rotate_r(t_nb **stack_a, t_nb **stack_b, int indice)
{
	rotate(*&stack_a, 2);
	rotate(*&stack_b, 2);
	if (indice == 2)
		ft_printf("rr\n");
}

void	reverse_rotate(t_nb **stack, int indice)
{
	t_nb	*temp;
	t_nb	*pre_last;
	t_nb	*beginning;

	if (!*stack || !(*stack)->next)
		return ;
	beginning = (*stack);
	while ((*stack)->next != NULL)
	{
		pre_last = (*stack);
		(*stack) = (*stack)->next;
	}
	temp = (*stack);
	if (pre_last)
		pre_last->next = NULL;
	temp->next = beginning;
	(*stack) = temp;
	if (indice == 0)
		ft_printf("rra\n");
	else if (indice == 1)
		ft_printf("rrb\n");
}
