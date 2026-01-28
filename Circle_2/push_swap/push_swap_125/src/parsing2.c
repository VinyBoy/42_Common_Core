/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:43:36 by viny              #+#    #+#             */
/*   Updated: 2025/02/16 16:41:04 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	ft_exit_error_2(t_nb **stack_a)
{
	ft_printf("Error\n");
	ft_lstclear_ps(stack_a);
	exit(EXIT_FAILURE);
}

void	ft_exit_error(t_nb **stack_a)
{
	ft_printf("Error\n");
	ft_lstclear_ps(stack_a);
	exit(EXIT_FAILURE);
}

void	ft_exit_error_new(t_nb **stack, char **cmd)
{
	ft_printf("Error\n");
	ft_free_double_array(cmd);
	ft_lstclear_ps(stack);
	exit(EXIT_FAILURE);
}

void	ft_free_double_array(char **tab)
{
	int	i;

	i = -1;
	if (!tab)
		return ;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

int	ft_atoi_ovrflw_quote(const char *string, t_nb **stack, char **cmd)
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
			ft_exit_error_new(stack, cmd);
		res = res * 10 + (*string - '0');
		string++;
	}
	return (res * signe);
}
