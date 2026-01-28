/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:29:18 by viny              #+#    #+#             */
/*   Updated: 2025/02/15 17:47:25 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	ft_parsing_quote_2(t_nb **stack_a, char **argv)
{
	int		i;
	int		j;
	int		nb;
	char	**cmd;

	i = -1;
	cmd = ft_split(argv[1], ' ');
	if (!cmd)
		ft_exit_error_new(stack_a, cmd);
	while (cmd[++i])
	{
		j = -1;
		while (cmd[i][++j])
		{
			if (ft_isdigit(cmd[i][j]) == 0)
				ft_exit_error_new(stack_a, cmd);
		}
		nb = ft_atoi_ovrflw(cmd[i], stack_a);
		add_to_stack(stack_a, nb);
	}
	ft_free_double_array(cmd);
	if (ft_is_dupplicate(stack_a) == 1)
		ft_exit_error(stack_a);
	put_index_stack(stack_a);
}

t_nb	**ft_nb_to_stack_2(int argc, char **argv, t_nb **stack_a)
{
	int		i;
	int		nb;

	i = 0;
	if (argc == 2)
		ft_parsing_quote_2(stack_a, argv);
	else
	{
		while (++i <= argc - 1)
		{
			if (ft_check_argv_is_digit(argv[i]) == 1)
				ft_exit_error_2(stack_a);
			else
			{
				nb = ft_atoi_ovrflw(argv[i], stack_a);
				add_to_stack(stack_a, nb);
			}
		}
	}
	if (ft_is_dupplicate(stack_a) == 1)
		ft_exit_error(stack_a);
	put_index_stack(stack_a);
	return (stack_a);
}
