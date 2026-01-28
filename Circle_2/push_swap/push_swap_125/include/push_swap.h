/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:01:30 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/02/16 16:40:50 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/include/libft.h"
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_pile_stats
{
	int	total;
	int	start;
	int	moyenne;
	int	first_quart;
	int	third_quart;
}	t_pile_stats;

typedef struct s_nb
{
	int			nb;
	int			index;
	struct s_nb	*next;
	struct s_nb	*prev;
}	t_nb;

/*parsing.c*/

void	add_to_stack(t_nb **stack, int the_nb);
int		ft_is_dupplicate(t_nb **stack);
int		ft_check_argv_is_digit(char *string);
t_nb	*ft_parsing_quote(t_nb **stack_a, char **argv);
t_nb	*ft_nb_to_stack(int argc, char **argv);

/*parsing2.c*/

void	ft_exit_error_2(t_nb **stack_a);
void	ft_exit_error_new(t_nb **stack, char **cmd);
void	ft_free_double_array(char **tab);
void	ft_exit_error(t_nb **stack_a);
int		ft_atoi_ovrflw_quote(const char *string, t_nb **stack, char **cmd);

/*utils.c*/

int		ft_atoi_ovrflw(const char *string, t_nb **stack);
void	print_stack(t_nb **stack_a);
int		a_is_sorted(t_nb *stack_a);
void	put_index_stack(t_nb **stack_a);
void	put_index_stack_index(t_nb *t, t_nb **s_s, int s_nb);

/*fonctions_listes*/

void	ft_lstadd_back_ps(t_nb **lst, t_nb *new);
void	ft_lstclear_ps(t_nb **lst);
int		ft_nb_of_list(t_nb *stack_a);

/*instructions_1.c*/

void	swap(t_nb **stack, int indice);
void	swap_ss(t_nb **stack_a, t_nb **stack_b, int indice);
void	rotate(t_nb **stack, int indice);
void	rotate_r(t_nb **stack_a, t_nb **stack_b, int indice);
void	reverse_rotate(t_nb **stack, int indice);

/*instructions_2.c*/

void	reverse_rotate_r(t_nb **stack_a, t_nb **stack_b, int indice);
void	push_a(t_nb **stack_a, t_nb **stack_b);
void	push_b(t_nb **stack_a, t_nb **stack_b);

/*Sort_few.c*/

void	ft_sort_few(t_nb **stack_a, t_nb **stack_b, int argc);
void	sort_two(t_nb **stack_a);
void	sort_three(t_nb **stack, int indice);
void	sort_four_five(t_nb **stack_a, t_nb **stack_b, int argc);
void	find_small_and_pb(t_nb **stack_a, t_nb **stack_b, int argc);

/*Sort_few_utils.c*/

void	ft_push_index_zero(t_nb **stack_a, t_nb **stack_b, int count);
void	ft_push_index_one(t_nb **stack_a, t_nb **stack_b, int count);

/*new_pre_sort_1*/

void	ft_sort_chunky(t_nb **stack_a, t_nb **stack_b);
void	init_stats(t_pile_stats *stats, t_nb **stack_a);
void	empty_stack_a(t_nb **stack_a, t_nb **stack_b, t_pile_stats *stats);
void	move_nb(t_nb **stack_a, t_nb **stack_b, int s, int end);
void	move_target(t_nb **stack_a, int start, int end, char *str);

/*new_pre_sort_2*/

int		ft_check_nb_exist(t_nb **stack, int start, int end);
int		nb_f_up(t_nb **stack, int start, int end);
int		nb_fdown(t_nb **stack, int start, int end);

/*checker.c*/

char	**ft_recover_stdin(t_nb **stack_a, t_nb **stack_b);
void	do_instruction(t_nb **stack_b, t_nb **stack_a, char **cmd);
int		do_instruction_2(t_nb **stack_a, t_nb **stack_b, char **cmd, int i);

/*checker_instructions.c*/
void	push_a_checker(t_nb **stack_a, t_nb **stack_b);
void	push_b_checker(t_nb **stack_a, t_nb **stack_b);

/*checker_utils.c*/

void	free_tab(t_nb **stack_a, t_nb **stack_b, char **cmd, int indice);
void	ret_error(t_nb **stack_a, t_nb **stack_b, char **cmd, int indice);
void	ft_exit_succes(int bool, char **cmd, t_nb **stack_a, t_nb **stack_b);
void	ft_exit_failure(t_nb **stack_a);
void	ft_exit(int bool, t_nb **stack_a, t_nb **stack_b);

/*checker_utils2.c*/

void	ft_parsing_quote_2(t_nb **stack, char **argv);
t_nb	**ft_nb_to_stack_2(int argc, char **argv, t_nb **stack_a);

/*Sort.c*/
void	ft_sort_all(t_nb **stack_a, t_nb **stack_b);
void	push_lower(t_nb **stack_a, t_nb **stack_b);
int		cost(t_nb *elem, t_nb **stack_a, t_nb **stack_b);
int		cost_to_top(t_nb *elem, t_nb **stack);
int		elem_position(t_nb *elem, t_nb *stack);

/*Sort_utils.c*/
t_nb	*find_target(t_nb *elem, t_nb **stack);
t_nb	*find_lower(t_nb **stack);
t_nb	*find_highest(t_nb **stack);
void	rotate_to_top(t_nb *elem, t_nb **stack, int indice);

/*reverse_rotate.c*/
void	rtt_both(t_nb *target, t_nb **s_a, t_nb *elem_b, t_nb **s_b);
void	update_pos_count(int *p_a, int *p_b, int *c_a, int *c_b);

#endif