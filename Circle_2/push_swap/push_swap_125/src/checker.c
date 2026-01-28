/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:39:37 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/02/15 17:47:39 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	main(int argc, char **argv)
{
	t_nb	*stack_a;
	t_nb	*stack_b;
	char	**cmd;

	ft_nb_to_stack_2(argc, argv, &stack_a);
	if (!stack_a)
		ft_exit_failure(&stack_a);
	stack_b = NULL;
	if (a_is_sorted(stack_a) == 1)
	{
		cmd = ft_recover_stdin(&stack_a, &stack_b);
		do_instruction(&stack_a, &stack_b, cmd);
	}
	else
		ft_exit(1, &stack_a, &stack_b);
	if (a_is_sorted(stack_a) == 0)
		ft_exit_succes(1, cmd, &stack_a, &stack_b);
	else
		ft_exit_succes(0, cmd, &stack_a, &stack_b);
	return (0);
}

char	**ft_recover_stdin(t_nb **stack_a, t_nb **stack_b)
{
	char	**tab_of_cmd;
	char	*temp;
	char	*str;

	temp = NULL;
	tab_of_cmd = NULL;
	str = ft_strdup("");
	if (str == NULL)
		free_tab(stack_a, stack_b, tab_of_cmd, 1);
	temp = get_next_line(0);
	while (temp != NULL)
	{
		str = ft_strjoin(str, temp);
		if (!str)
			free_tab(stack_a, stack_b, tab_of_cmd, 1);
		temp = get_next_line(0);
	}
	tab_of_cmd = ft_split(str, '\n');
	free (str);
	return (tab_of_cmd);
}

void	do_instruction(t_nb **stack_a, t_nb **stack_b, char **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i] != NULL)
	{
		if (cmd[i][0] == 's' && cmd[i][1] == 'a' && cmd[i][2] == '\0')
			swap(stack_a, 2);
		else if (cmd[i][0] == 's' && cmd[i][1] == 'b' && cmd[i][2] == '\0')
			swap(stack_b, 2);
		else if (cmd[i][0] == 's' && cmd[i][1] == 's' && cmd[i][2] == '\0')
			swap_ss(stack_a, stack_b, 3);
		else if (cmd[i][0] == 'r' && cmd[i][1] == 'a' && cmd[i][2] == '\0')
			rotate(stack_a, 2);
		else if (cmd[i][0] == 'r' && cmd[i][1] == 'b' && cmd[i][2] == '\0')
			rotate(stack_b, 2);
		else if (cmd[i][0] == 'r' && cmd[i][1] == 'r' && cmd[i][2] == '\0')
			rotate_r(stack_a, stack_b, 3);
		else if (do_instruction_2(stack_a, stack_b, cmd, i) == 0)
			ret_error(stack_a, stack_b, cmd, 1);
	}
}

int	do_instruction_2(t_nb **stack_a, t_nb **stack_b, char **cmd, int i)
{
	if (cmd[i][0] == 'r' && cmd[i][1] == 'r' && cmd[i][2] == 'a'
		&& cmd[i][3] == '\0')
		return (reverse_rotate(stack_a, 2), 1);
	else if (cmd[i][0] == 'r' && cmd[i][1] == 'r' && cmd[i][2] == 'b'
		&& cmd[i][3] == '\0')
		return (reverse_rotate(stack_b, 2), 1);
	else if (cmd[i][0] == 'r' && cmd[i][1] == 'r' && cmd[i][2] == 'r'
		&& cmd[i][3] == '\0')
		return (reverse_rotate_r(stack_a, stack_b, 3), 1);
	else if (cmd[i][0] == 'p' && cmd[i][1] == 'a' && cmd[i][2] == '\0')
		return (push_a_checker(stack_a, stack_b), 1);
	else if (cmd[i][0] == 'p' && cmd[i][1] == 'b' && cmd[i][2] == '\0')
		return (push_b_checker(stack_a, stack_b), 1);
	return (0);
}
