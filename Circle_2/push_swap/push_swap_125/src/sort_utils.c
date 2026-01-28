/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 19:19:04 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/02/06 19:05:21 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

t_nb	*find_target(t_nb *elem, t_nb **stack)
{
	t_nb	*target;
	t_nb	*current;

	if (find_highest(stack)->index < elem->index)
		return (find_lower(stack));
	current = (*stack);
	target = find_highest(stack);
	while (current != NULL)
	{
		if (current->index > elem->index && current->index < target->index)
		{
			target = current;
		}
		current = current->next;
	}
	return (target);
}

t_nb	*find_lower(t_nb **stack)
{
	t_nb	*current;
	t_nb	*lower;

	if (*stack == NULL)
		return (NULL);
	current = (*stack);
	lower = (*stack);
	while (current != NULL)
	{
		if (current->index < lower->index)
			lower = current;
		current = current->next;
	}
	return (lower);
}

t_nb	*find_highest(t_nb **stack)
{
	t_nb	*current;
	t_nb	*highest;

	if ((*stack) == NULL)
		return (NULL);
	current = (*stack);
	highest = (*stack);
	while (current != NULL)
	{
		if (current->index > highest->index)
			highest = current;
		current = current->next;
	}
	return (highest);
}
