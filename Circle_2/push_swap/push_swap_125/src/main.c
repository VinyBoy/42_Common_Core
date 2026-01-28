/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:54:06 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/02/15 16:23:25 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	main(int argc, char **argv)
{
	t_nb	*stack_a;
	t_nb	*stack_b;

	if (argc < 2)
		exit (1);
	stack_a = ft_nb_to_stack(argc, argv);
	stack_b = NULL;
	if (!stack_a)
		ft_exit_error(&stack_a);
	argc = ft_nb_of_list(stack_a) + 1;
	if (a_is_sorted(stack_a) == 1)
	{
		if (argc < 5)
			ft_sort_few(&stack_a, &stack_b, argc);
		else
			ft_sort_all(&stack_a, &stack_b);
	}
	ft_lstclear_ps(&stack_a);
	ft_lstclear_ps(&stack_b);
}
