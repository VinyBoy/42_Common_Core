/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:24:05 by viny              #+#    #+#             */
/*   Updated: 2023/06/24 18:43:31 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <limits.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <fcntl.h>
# include "../libft/Libft/libft.h"

typedef struct s_nb
{
	int			nb;
	int			index;
	struct s_nb	*next;
}	t_nb;

void	ft_exit_error(t_nb **stack);
void	ft_lstadd_back_ps(t_nb **lst, t_nb *new);
void	ft_lstclear_ps(t_nb **lst);
void	swap(t_nb **stack, char c);
void	swap_ss(t_nb **stack_a, t_nb **stack_b, char c);
void	rotate(t_nb **stack, char c);
void	rotate_r(t_nb **stack_a, t_nb **stack_b, char c);
void	reverse_rotate(t_nb **stack, char c);
void	reverse_rotate_r(t_nb **stack_a, t_nb **stack_b, char c);
void	push_a(t_nb **stack_a, t_nb **stack_b);
void	push_b(t_nb **stack_a, t_nb **stack_b);
int		main(int argc, char **argv);
void	add_to_stack(t_nb **stack, int the_nb);
int		ft_is_dupplicate(t_nb **stack);
int		ft_check_argv_is_digit(char *string);
t_nb	*ft_nb_to_stack(int argc, char **argv);
void	ft_sort_few(t_nb **stack_a, t_nb **stack_b, int argc);
void	sort_two(t_nb **stack_a);
void	sort_three(t_nb **stack_a);
int		return_pos(t_nb **stack);
void	sort_pa_five_moove_i_three(t_nb **stack_a);
void	sort_pa_five_moove_i_four(t_nb **stack_a);
void	sort_pa_four(t_nb **stack_a);
void	sort_pa_five(t_nb **stack_a);
int		a_is_sorted(t_nb *stack_a);
int		ft_atoi_ovrflw(const char *string, t_nb **stack);
int		ft_strcmp(const char *s1, const char *s2);
void	radix_sort(t_nb **stack_a, t_nb **stack_b, int argc);
int		nb_node(t_nb *stack);
int		ft_bits_len(int argc);
void	print_stack(t_nb **stack_a);
void	put_index_stack(t_nb **stack_a);
void	put_index_stack_index(t_nb *t, t_nb **s_s, int s_nb);
void	sort_four_five(t_nb **stack_a, t_nb **stack_b, int argc);
void	find_small_and_pb(t_nb **stack_a, t_nb **stack_b, int argc);
void	ft_push_index_zero(t_nb **stack_a, t_nb **stack_b, int count);
void	ft_push_index_one(t_nb **stack_a, t_nb **stack_b, int count);

#endif
