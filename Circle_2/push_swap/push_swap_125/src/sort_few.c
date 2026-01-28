/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_few.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:10:18 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/02/15 11:45:16 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	ft_sort_few(t_nb **stack_a, t_nb **stack_b, int argc)
{
	if (argc == 3)
		sort_two(stack_a);
	else if (argc == 4)
		sort_three(stack_a, 0);
	else if (argc == 5 || argc == 6)
		sort_four_five(stack_a, stack_b, argc);
}

void	sort_two(t_nb **stack_a)
{
	if (a_is_sorted(*stack_a) == 1)
		swap(stack_a, 0);
}

void	sort_three(t_nb **stack, int indice)
{
	const int	a = (*stack)->index;
	const int	b = (*stack)->next->index;
	const int	c = (*stack)->next->next->index;

	if (a_is_sorted(*stack) == 1)
	{
		if (a > b && b < c && a < c)
			swap(stack, indice);
		if (a < b && b > c && a > c)
			reverse_rotate(stack, indice);
		if (a > b && b < c && a > c)
			rotate(stack, indice);
		if (a < b && b > c && a < c)
		{
			swap(stack, indice);
			rotate(stack, indice);
		}
		if (a > b && b > c && a > c)
		{
			swap(stack, indice);
			reverse_rotate(stack, indice);
		}
	}
}

void	sort_four_five(t_nb **stack_a, t_nb **stack_b, int argc)
{
	if (argc == 5)
	{
		find_small_and_pb(stack_a, stack_b, argc);
		sort_three(stack_a, 0);
		push_a(stack_a, stack_b);
	}
	if (argc == 6)
	{
		find_small_and_pb(stack_a, stack_b, argc);
		sort_three(stack_a, 0);
		push_a(stack_a, stack_b);
		push_a(stack_a, stack_b);
	}
}

void	find_small_and_pb(t_nb **stack_a, t_nb **stack_b, int argc)
{
	t_nb	*temp;
	int		count;

	count = 0;
	temp = (*stack_a);
	while (temp && temp != NULL)
	{
		count++;
		if (temp->index == 0)
			ft_push_index_zero(stack_a, stack_b, count);
		temp = temp->next;
	}
	if (argc == 6)
	{
		count = 0;
		temp = (*stack_a);
		while (temp && temp != NULL)
		{
			count++;
			if (temp->index == 1)
				ft_push_index_one(stack_a, stack_b, count);
			temp = temp->next;
		}
	}
}
