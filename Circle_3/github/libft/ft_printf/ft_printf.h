/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:17:10 by marvin            #+#    #+#             */
/*   Updated: 2023/06/21 15:35:52 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# define STD_OUT 1

int			format(const char *str, int i, va_list arg);
int			ft_printf(const char *str, ...);
int			ft_strlen_printf(char *str);
int			ft_putstr(char *str);
int			ft_putstr(char *str);
int			ft_print_char(char c);
int			ft_print_str(char *str);
int			ft_tcheck(int n);
char		*ft_itoa(int n);
int			ft_print_nbr(int n);
int			ft_uputstr(char *str);
int			ft_unsigned_tcheck(unsigned int n);
char		*ft_unsigned_itoa(unsigned int n);
int			ft_print_unsigned_nbr(unsigned int n);
int			ft_hex_len(unsigned	int num);
void		ft_put_hex(unsigned int num, const char format);
int			ft_print_hex(unsigned int num, const char format);
int			ptrbase(unsigned long num, char *base, int *len);
int			put_ptr(void *ptr);

#endif