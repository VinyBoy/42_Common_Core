/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:16:41 by vnieto-j          #+#    #+#             */
/*   Updated: 2024/11/20 13:10:12 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *TheString)
{
	int	i;
	int	res;
	int	signe;

	i = 0;
	res = 0;
	signe = 1;
	while (TheString[i] == 32 || (TheString[i] >= 9 && TheString[i] <= 13))
		i++;
	if (TheString[i] == '-' || TheString[i] == '+')
	{
		if (TheString[i] == '-')
			signe *= -1;
		i++;
	}
	while (TheString[i] >= 48 && TheString[i] <= 57)
	{
		res = res * 10 + TheString[i] - 48;
		i++;
	}
	return (res * signe);
}

// #include <stdio.h>
// #include <stdlib.h>

// int main()
// {
// 	printf("%d\n", ft_atoi("-54"));
// 	printf("%d\n", atoi("-54"));

// }