/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:52:23 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/06/20 15:05:21 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	a_is_sorted(t_nb *stack_a)
{
	t_nb	*temp;

	temp = stack_a;
	while (temp->next)
	{
		if (temp->nb > temp->next->nb)
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	ft_bits_len(int argc)
{
	int	len;

	len = 0;
	while (argc)
	{
		len++;
		argc /= 2;
	}
	return (len);
}

int	nb_node(t_nb *stack)
{
	int	i;

	i = 0;
	while (stack)
	{
		i++;
		stack = stack->next;
	}
	return (i);
}

void	radix_sort(t_nb **stack_a, t_nb **stack_b, int argc)
{
	int	i;
	int	bits;
	int	arg;

	i = 0;
	bits = ft_bits_len(argc);
	while (i < bits)
	{
		arg = argc - 1;
		while (arg--)
		{
			if (((*stack_a)->index >> i & 1) == 0)
				push_b(stack_a, stack_b);
			else
				rotate(stack_a, 'a');
		}
		while (nb_node(*stack_b) != 0)
			push_a(stack_a, stack_b);
		i++;
	}
}
