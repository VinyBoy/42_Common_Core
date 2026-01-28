/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:14:13 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/06/23 14:38:45 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_exit_error(t_nb **stack)
{
	ft_printf("Error\n");
	ft_lstclear_ps(stack);
	exit(EXIT_FAILURE);
}

void	add_to_stack(t_nb **stack, int the_nb)
{
	t_nb	*new;

	new = malloc(sizeof(t_nb));
	if (!new)
		ft_exit_error(stack);
	new->nb = the_nb;
	new->index = -1;
	new->next = NULL;
	ft_lstadd_back_ps(stack, new);
}

int	ft_is_dupplicate(t_nb **stack)
{
	t_nb	*current;
	t_nb	*check;

	current = (*stack);
	while (current != NULL)
	{
		check = current->next;
		while (check != NULL)
		{
			if (current->nb == check->nb)
				return (1);
			check = check->next;
		}
		current = current->next;
	}
	return (0);
}

int	ft_check_argv_is_digit(char *string)
{
	if (!string)
		return (1);
	while (*string != '\0')
	{
		if (!(*string >= '0' && *string <= '9') && *string != '-')
			return (1);
		string++;
	}
	return (0);
}

t_nb	*ft_nb_to_stack(int argc, char **argv)
{
	int		i;
	int		nb;
	t_nb	*stack;

	i = 1;
	stack = NULL;
	while (i <= argc - 1)
	{
		if (ft_check_argv_is_digit(argv[i]) == 1)
			ft_exit_error(&stack);
		else
		{
			nb = ft_atoi_ovrflw(argv[i], &stack);
			add_to_stack(&stack, nb);
		}
		i++;
	}
	if (ft_is_dupplicate(&stack) == 1)
		ft_exit_error(&stack);
	put_index_stack(&stack);
	return (stack);
}
