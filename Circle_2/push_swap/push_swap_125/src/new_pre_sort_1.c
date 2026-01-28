/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pre_sort_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:32:16 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/02/10 19:34:58 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	ft_sort_chunky(t_nb **stack_a, t_nb **stack_b)
{
	t_pile_stats	*stats;

	stats = malloc(sizeof(t_pile_stats));
	if (!stats)
		return ;
	init_stats(stats, stack_a);
	empty_stack_a(stack_a, stack_b, stats);
}

void	init_stats(t_pile_stats *stats, t_nb **stack_a)
{
	stats->start = 0;
	stats->total = ft_nb_of_list(*stack_a);
	stats->moyenne = stats->total / 2;
	stats->first_quart = stats->moyenne / 2;
	stats->third_quart = stats->first_quart + stats->moyenne;
}

void	empty_stack_a(t_nb **stack_a, t_nb **stack_b, t_pile_stats *stats)
{
	while (ft_nb_of_list((*stack_a)) > 3)
	{
		move_nb(stack_a, stack_b, 0, stats->first_quart);
		move_nb(stack_a, stack_b, stats->first_quart, stats->moyenne);
		move_nb(stack_a, stack_b, stats->moyenne, stats->third_quart);
		move_nb(stack_a, stack_b, stats->third_quart, stats->total - 3);
	}
}

void	move_nb(t_nb **stack_a, t_nb **stack_b, int s, int end)
{
	int	mid_quart;

	mid_quart = (s + end) / 2;
	while (ft_check_nb_exist(stack_a, s, end) && ft_nb_of_list(*stack_a) > 3)
	{
		if (nb_f_up(stack_a, s, end) < nb_fdown(stack_a, s, end))
			move_target(stack_a, s, end, "up");
		else if (nb_f_up(stack_a, s, end) >= nb_fdown(stack_a, s, end))
			move_target(stack_a, s, end, "down");
		if ((*stack_a)->index >= s || (*stack_a)->index < end)
		{
			push_b(stack_a, stack_b);
		}
		if (ft_nb_of_list(*stack_b) > 1)
			if ((*stack_b)->index <= mid_quart)
				rotate(stack_b, 1);
	}
}

void	move_target(t_nb **stack_a, int start, int end, char *str)
{
	t_nb	*temp;

	temp = (*stack_a);
	if (ft_strcmp(str, "up") == 0)
	{
		while (temp->index < start || temp->index > end)
		{
			rotate(stack_a, 0);
			temp = (*stack_a);
		}
	}
	else if (ft_strcmp(str, "down") == 0)
	{
		while (temp->index < start || temp->index > end)
		{
			reverse_rotate(stack_a, 0);
			temp = (*stack_a);
		}
	}
}
