/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:55:17 by vnieto-j          #+#    #+#             */
/*   Updated: 2024/11/29 18:34:02 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

//get_next_line.c
char	*init_buffer(void);
char	*get_next_line(int fd);
char	*ft_join(char *buff, char *stash);
char	*ft_join_new_line_detected(char *bf, char *stash);
char	*ft_condition(char stash[BUFFER_SIZE], int fd, char *buffer, int n);
//get_next_line_utils.c
int		ft_check_new_line(char *str);
int		ft_one(char *stash);
int		strln(char *str);
int		strlnao(char *str, char c);
void	ft_init_and_put_one(char *stash, char c);

#endif
