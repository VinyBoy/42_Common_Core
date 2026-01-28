/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:45:41 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/02/10 18:15:52 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	ft_sort_all(t_nb **stack_a, t_nb **stack_b)
{
	int	size_stack;

	size_stack = ft_nb_of_list((*stack_a));
	if (size_stack <= 100)
		while (ft_nb_of_list((*stack_a)) > 3)
			push_b(stack_a, stack_b);
	else if (size_stack > 100)
		ft_sort_chunky(stack_a, stack_b);
	sort_three(stack_a, 0);
	while ((*stack_b) != NULL)
		push_lower(stack_a, stack_b);
	rotate_to_top(find_lower(stack_a), stack_a, 0);
}

void	push_lower(t_nb **stack_a, t_nb **stack_b)
{
	t_nb	*lower;
	t_nb	*current;

	lower = (*stack_b);
	current = (*stack_b);
	while (current != NULL)
	{
		if (cost(lower, stack_a, stack_b) > cost(current, stack_a, stack_b))
			lower = current;
		current = current->next;
	}
	rtt_both(find_target(lower, stack_a), stack_a, lower, stack_b);
	push_a(stack_a, stack_b);
}

int	cost(t_nb *elem, t_nb **stack_a, t_nb **stack_b)
{
	t_nb	*target;
	int		cost;

	target = find_target(elem, stack_a);
	cost = cost_to_top(elem, stack_b) + cost_to_top(target, stack_a);
	return (cost);
}

int	cost_to_top(t_nb *elem, t_nb **stack)
{
	int	cost;

	if (elem_position(elem, (*stack)) <= ft_nb_of_list((*stack)) / 2)
		cost = elem_position(elem, (*stack));
	else
		cost = ft_nb_of_list((*stack)) - elem_position(elem, (*stack));
	return (cost);
}

int	elem_position(t_nb *elem, t_nb *stack)
{
	int	position;

	position = 0;
	while (stack != NULL)
	{
		if (stack == elem)
			return (position);
		stack = stack->next;
		position++;
	}
	return (-1);
}
