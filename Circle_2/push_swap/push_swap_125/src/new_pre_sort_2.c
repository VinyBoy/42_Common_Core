/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pre_sort_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:37:52 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/02/10 19:35:05 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	nb_f_up(t_nb **stack, int start, int end)
{
	t_nb	*temp;
	int		count;

	count = 0;
	temp = *(stack);
	while (temp->next != NULL)
	{
		if (temp->index >= start && temp->index <= end)
		{
			return (count);
		}
		temp = temp->next;
		count++;
	}
	return (count);
}

int	nb_fdown(t_nb **stack, int start, int end)
{
	t_nb	*temp;
	int		pos;
	int		count;
	int		result;

	temp = (*stack);
	pos = 0;
	result = 0;
	count = ft_nb_of_list(*stack);
	while (temp != NULL)
	{
		if (temp->index >= start && temp->index <= end)
			result = count - pos;
		pos++;
		temp = temp->next;
	}
	return (result);
}

int	ft_check_nb_exist(t_nb **stack, int start, int end)
{
	t_nb	*temp;

	temp = (*stack);
	while (temp != NULL)
	{
		if (temp->index >= start && temp->index <= end)
			return (1);
		temp = temp->next;
	}
	return (0);
}
