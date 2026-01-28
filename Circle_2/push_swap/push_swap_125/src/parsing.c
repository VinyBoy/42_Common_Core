/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:43:06 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/02/15 18:25:03 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

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

t_nb	*ft_parsing_quote(t_nb **stack, char **argv)
{
	int		i;
	int		j;
	int		nb;
	char	**cmd;

	i = -1;
	cmd = ft_split(argv[1], ' ');
	if (!cmd)
		ft_exit_error_new(stack, cmd);
	while (cmd[++i])
	{
		j = -1;
		while (cmd[i][++j])
		{
			if (ft_isdigit(cmd[i][j]) == 0)
				ft_exit_error_new(stack, cmd);
		}
		nb = ft_atoi_ovrflw_quote(cmd[i], stack, cmd);
		add_to_stack(stack, nb);
	}
	ft_free_double_array(cmd);
	if (ft_is_dupplicate(stack) == 1)
		ft_exit_error(stack);
	put_index_stack(stack);
	return (*stack);
}

t_nb	*ft_nb_to_stack(int argc, char **argv)
{
	int		i;
	int		nb;
	t_nb	*stack;

	i = 0;
	stack = NULL;
	if (argc == 2)
		stack = ft_parsing_quote(&stack, argv);
	else
	{
		while (++i <= argc - 1)
		{
			if (ft_check_argv_is_digit(argv[i]) == 1)
				ft_exit_error(&stack);
			else
			{
				nb = ft_atoi_ovrflw(argv[i], &stack);
				add_to_stack(&stack, nb);
			}
		}
	}
	if (ft_is_dupplicate(&stack) == 1)
		ft_exit_error(&stack);
	put_index_stack(&stack);
	return (stack);
}
