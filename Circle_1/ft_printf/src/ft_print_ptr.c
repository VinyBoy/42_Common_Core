/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:57:41 by vnieto-j          #+#    #+#             */
/*   Updated: 2024/11/26 18:10:33 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	ft_ptr_base(unsigned long num, char *base, int *len)
{
	if (num > 15)
		ft_ptr_base((num / 16), base, len);
	*len += write(1, &base[num % 16], 1);
}

void	ft_put_ptr(void *ptr, int *len)
{
	unsigned long	num;

	if (ptr == NULL)
		*len += write(1, "(nil)", 5);
	else
	{
		num = (unsigned long) ptr;
		*len += write(1, "0x", 2);
		ft_ptr_base(num, "0123456789abcdef", len);
	}
}
