/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:03:27 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/02/10 18:31:51 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	rotate_to_top(t_nb *elem, t_nb **stack, int indice)
{
	if (elem_position(elem, (*stack)) <= ft_nb_of_list((*stack)) / 2)
		while (elem != (*stack))
			rotate(stack, indice);
	else
		while (elem != (*stack))
			reverse_rotate(stack, indice);
}

void	rtt_both(t_nb *target, t_nb **s_a, t_nb *elem_b, t_nb **s_b)
{
	int	p_a;
	int	p_b;
	int	c_a;
	int	c_b;

	p_a = elem_position(target, *s_a);
	p_b = elem_position(elem_b, *s_b);
	c_a = ft_nb_of_list(*s_a);
	c_b = ft_nb_of_list(*s_b);
	while (p_a > 0 && p_b > 0 && ((p_a <= c_a / 2 && p_b <= c_b / 2)
			|| (p_a > c_a / 2 && p_b > c_b / 2)))
	{
		if (p_a <= c_a / 2 && p_b <= c_b / 2)
			rotate_r(s_a, s_b, 2);
		else
			reverse_rotate_r(s_a, s_b, 2);
		update_pos_count(&p_a, &p_b, &c_a, &c_b);
	}
	rotate_to_top(target, s_a, 0);
	rotate_to_top(elem_b, s_b, 1);
}

void	update_pos_count(int *p_a, int *p_b, int *c_a, int *c_b)
{
	if ((*p_a) > (*c_a) / 2)
		(*p_a) = ((*p_a) + 1) % (*c_a);
	else
		(*p_a)--;
	if ((*p_b) > (*c_b) / 2)
		(*p_b) = (*p_b + 1) % (*c_b);
	else
		(*p_b)--;
}
