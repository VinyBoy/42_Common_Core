/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:59:44 by vnieto-j          #+#    #+#             */
/*   Updated: 2024/11/27 15:35:59 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	ft_print_str(char *str, int *len)
{
	int	i;

	i = 0;
	if (str == NULL)
		*len = *len + write(1, "(null)", 6);
	else
	{
		while (str[i])
		{
			ft_print_char(str[i], len);
			i++;
		}
	}
}

void	ft_print_char(int c, int *len)
{
	write(1, &c, 1);
	(*len)++;
}

static int	tcheck(int n)
{
	unsigned int	nb;
	int				count;

	count = 1;
	if (n < 0)
	{
		count++;
		n = n * -1;
	}
	nb = n;
	while (nb > 9)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char			*dest;
	int				lenght;
	unsigned int	nb;

	lenght = tcheck(n);
	dest = (char *)malloc(sizeof(char) * (lenght + 1));
	if (dest == NULL)
		return (NULL);
	dest[lenght--] = '\0';
	if (n == 0)
		dest[0] = '0';
	if (n < 0)
	{
		n = n * -1;
		dest[0] = '-';
	}
	nb = n;
	while (nb > 0)
	{
		dest[lenght] = (nb % 10) + 48;
		nb = nb / 10;
		lenght--;
	}
	return (dest);
}
