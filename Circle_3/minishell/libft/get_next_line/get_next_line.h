/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:47:54 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/04/14 15:29:21 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

int		ft_one(char *stash);
char	*ft_join(char *buff, char *stash);
int		ft_check_new_line(char *stash);
int		strln(char *str);
int		strlnao(char *str, char c);
void	init_and_put_one(char *stash, char c);
char	*ft_join(char *buff, char *stash);
char	*ft_join_new_line(char *buff, char *stash);
char	*get_next_line(int fd);
char	*init_buff(void);
char	*ft_condtion(char stash[BUFFER_SIZE], int fd, char *buff);

#endif