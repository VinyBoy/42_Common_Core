/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:03:34 by vnieto-j          #+#    #+#             */
/*   Updated: 2024/11/27 15:34:33 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>

/*ft_print_hexa.c*/
int				ft_hex_len(unsigned int num);
void			ft_put_hex(unsigned int num, const char format, int *len);
void			ft_print_hex(unsigned int num, const char format, int *len);
/*ft_print_nb.c*/
void			ft_print_nbr(int n, int *len);
unsigned int	ft_unsigned_check(unsigned int n);
char			*ft_unsigned_itoa(unsigned int n);
void			ft_print_unsigned_nbr(unsigned int nb, int *len);
/*ft_print_ptr.c*/
void			ft_ptr_base(unsigned long num, char *base, int *len);
void			ft_put_ptr(void *ptr, int *len);
/*ft_print_str.c*/
void			ft_print_str(char *str, int *len);
void			ft_print_char(int c, int *len);
char			*ft_itoa(int n);
/*ft_printf.c*/
void			format(const char *str, int i, va_list arg, int *len);
int				ft_printf(const char *str, ...);

#endif