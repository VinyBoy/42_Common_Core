/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:43:22 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/02/16 16:40:17 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	print_stack(t_nb **stack_a)
{
	int		i;
	t_nb	*temp;

	i = 1;
	temp = (*stack_a);
	while (temp)
	{
		ft_printf("%d noeud = %d et index = %d\n", i, temp->nb, temp->index);
		i++;
		temp = temp->next;
	}
}

int	ft_atoi_ovrflw(const char *string, t_nb **stack)
{
	int	res;
	int	signe;

	signe = 1;
	res = 0;
	if (ft_strcmp(string, "-2147483648") == 0)
		return (-2147483648);
	if (*string == '-' || *string == '+')
	{
		if (*string == '-')
			signe *= -1;
		string++;
	}
	while (*string >= '0' && *string <= '9')
	{
		if (res > INT_MAX / 10 || (res == INT_MAX / 10
				&& (*string - '0') > INT_MAX % 10))
			ft_exit_error(stack);
		res = res * 10 + (*string - '0');
		string++;
	}
	return (res * signe);
}

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

void	put_index_stack(t_nb **stack_a)
{
	t_nb	*temp;
	t_nb	*stock_small;
	int		i;
	int		s_nb;

	i = 0;
	while (1)
	{
		temp = (*stack_a);
		stock_small = NULL;
		s_nb = INT_MAX;
		put_index_stack_index(temp, &stock_small, s_nb);
		if (stock_small == NULL)
			break ;
		else
		{
			stock_small->index = i;
			i++;
		}
	}
}

void	put_index_stack_index(t_nb *t, t_nb **s_s, int s_nb)
{
	while (t != NULL)
	{
		if (t->index == -1 && s_nb >= t->nb)
		{
			s_nb = t->nb;
			*s_s = t;
		}
		t = t->next;
	}
}
