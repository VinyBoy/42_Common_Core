/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:16:41 by vnieto-j          #+#    #+#             */
/*   Updated: 2024/11/20 19:15:16 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

// #include <stdio.h>
// #include <limits.h>

// int main()
// {
// 	printf("%s\n", ft_itoa(-10));
// }