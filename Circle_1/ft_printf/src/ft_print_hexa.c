/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:58:11 by vnieto-j          #+#    #+#             */
/*   Updated: 2024/11/26 18:03:21 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_hex_len(unsigned int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

void	ft_put_hex(unsigned int num, const char format, int *len)
{
	if (num >= 16)
	{
		ft_put_hex(num / 16, format, len);
		ft_put_hex(num % 16, format, len);
	}
	else
	{
		if (num <= 9)
			ft_print_char((num + 48), len);
		else
		{
			if (format == 'x')
				ft_print_char((num - 10 + 'a'), len);
			if (format == 'X')
				ft_print_char((num - 10 + 'A'), len);
		}
	}
}

void	ft_print_hex(unsigned int num, const char format, int *len)
{
	if (num == 0)
		*len += write(1, "0", 1);
	else
		ft_put_hex(num, format, len);
}
