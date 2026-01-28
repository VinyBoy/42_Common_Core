/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:41:33 by vnieto-j          #+#    #+#             */
/*   Updated: 2024/11/26 15:49:17 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	ft_print_nbr(int n, int *len)
{
	char	*temp_len;

	temp_len = ft_itoa(n);
	ft_print_str(temp_len, len);
	free (temp_len);
}

unsigned int	ft_unsigned_check(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		len++;
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_unsigned_itoa(unsigned int n)
{
	char			*dest;
	unsigned int	len;

	len = ft_unsigned_check(n);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	dest[len--] = '\0';
	while (n != '\0')
	{
		dest[len] = (n % 10) + 48;
		n = n / 10;
		len--;
	}
	return (dest);
}

void	ft_print_unsigned_nbr(unsigned int nb, int *len)
{
	char	*temp_len;

	if (nb == 0)
		*len += write(1, "0", 1);
	else
	{
		temp_len = ft_unsigned_itoa(nb);
		ft_print_str(temp_len, len);
		free (temp_len);
	}
}
