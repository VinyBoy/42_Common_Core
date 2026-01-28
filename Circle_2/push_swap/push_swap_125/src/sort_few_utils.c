/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_few_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:39:15 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/01/21 18:24:02 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	ft_push_index_zero(t_nb **stack_a, t_nb **stack_b, int count)
{
	if (count == 1)
		push_b(stack_a, stack_b);
	if (count == 2)
	{
		swap(stack_a, 'a');
		push_b(stack_a, stack_b);
	}
	if (count == 3)
	{
		rotate(stack_a, 'a');
		rotate(stack_a, 'a');
		push_b(stack_a, stack_b);
	}
	if (count == 4)
	{
		reverse_rotate(stack_a, 'a');
		reverse_rotate(stack_a, 'a');
		push_b(stack_a, stack_b);
	}
	if (count == 5)
	{
		reverse_rotate(stack_a, 'a');
		push_b(stack_a, stack_b);
	}
}

void	ft_push_index_one(t_nb **stack_a, t_nb **stack_b, int count)
{
	if (count == 1)
		push_b(stack_a, stack_b);
	if (count == 2)
	{
		swap(stack_a, 'a');
		push_b(stack_a, stack_b);
	}
	if (count == 3)
	{
		rotate(stack_a, 'a');
		rotate(stack_a, 'a');
		push_b(stack_a, stack_b);
	}
	if (count == 4)
	{
		reverse_rotate(stack_a, 'a');
		reverse_rotate(stack_a, 'a');
		push_b(stack_a, stack_b);
	}
}
