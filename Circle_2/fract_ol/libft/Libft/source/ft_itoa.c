/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:24:47 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/07/21 12:36:56 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	tcheck(int n)
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
	int				lengh;
	unsigned int	nb;

	lengh = tcheck(n);
	dest = (char *)malloc(sizeof(char) * (lengh + 1));
	if (dest == NULL)
		return (NULL);
	dest[lengh--] = '\0';
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
		dest[lengh] = (nb % 10) + 48;
		nb = nb / 10;
		lengh--;
	}
	return (dest);
}

// #include <stdio.h>
// #include <limits.h>

// int main()
// {
// 	printf("%s\n", ft_itoa(-10));
// }