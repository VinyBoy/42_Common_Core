/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:06:40 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/02/15 16:48:22 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	free_tab(t_nb **stack_a, t_nb **stack_b, char **cmd, int indice)
{
	int	i;

	i = -1;
	ft_lstclear_ps(stack_a);
	ft_lstclear_ps(stack_b);
	while (cmd[++i] != NULL)
		free(cmd[i]);
	free (cmd);
	if (indice == 1)
		exit(EXIT_FAILURE);
}

void	ret_error(t_nb **stack_a, t_nb **stack_b, char **cmd, int indice)
{
	write (2, "Error\n", 6);
	free_tab(stack_a, stack_b, cmd, indice);
}

void	ft_exit_succes(int bool, char **cmd, t_nb **stack_a, t_nb **stack_b)
{
	if (bool == 1)
		write (1, "OK\n", 3);
	if (bool == 0)
		write (1, "KO\n", 3);
	free_tab(stack_a, stack_b, cmd, 1);
}

void	ft_exit_failure(t_nb **stack_a)
{
	write (1, "Error\n", 6);
	ft_lstclear_ps(stack_a);
	exit(EXIT_FAILURE);
}

void	ft_exit(int bool, t_nb **stack_a, t_nb **stack_b)
{
	if (bool == 1)
		write (1, "OK\n", 3);
	if (bool == 0)
		write (1, "KO\n", 3);
	ft_lstclear_ps(stack_a);
	ft_lstclear_ps(stack_b);
	if (bool == 1)
		exit(EXIT_FAILURE);
}
