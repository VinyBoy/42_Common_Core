/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_few_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:07:03 by viny              #+#    #+#             */
/*   Updated: 2023/06/21 17:52:02 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	return_pos(t_nb **stack)
{
	int		i;
	int		the_nb;
	t_nb	*temp;

	i = 1;
	if (!(*stack))
		return (0);
	temp = (*stack);
	the_nb = temp->nb;
	while (temp && temp->next != NULL)
	{
		if (the_nb > temp->next->nb)
			i++;
		else if (the_nb < temp->next->nb)
			return (i);
		temp = temp->next;
	}
	return (i);
}

void	sort_pa_five_moove_i_four(t_nb **stack_a)
{
	reverse_rotate(stack_a, 'a');
	swap(stack_a, 'a');
	rotate(stack_a, 'a');
	rotate(stack_a, 'a');
}

void	sort_pa_five_moove_i_three(t_nb **stack_a)
{
	swap(stack_a, 'a');
	rotate(stack_a, 'a');
	swap(stack_a, 'a');
	reverse_rotate(stack_a, 'a');
}

void	sort_pa_five(t_nb **stack_a)
{
	int	i;

	i = return_pos(stack_a);
	if (i == 1)
		;
	else if (i == 2)
		swap(stack_a, 'a');
	else if (i == 3)
		sort_pa_five_moove_i_three(stack_a);
	else if (i == 4)
		sort_pa_five_moove_i_four(stack_a);
	else if (i == 5)
		rotate(stack_a, 'a');
	else
		ft_exit_error(stack_a);
}
