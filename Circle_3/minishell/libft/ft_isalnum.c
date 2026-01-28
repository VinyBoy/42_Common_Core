/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:54:58 by vnieto-j          #+#    #+#             */
/*   Updated: 2022/12/21 14:40:47 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (c >= 48 && c <= 57)
	{
		return (1);
	}
	if (c >= 65 && c <= 90)
	{
		return (1);
	}
	if (c >= 97 && c <= 122)
	{
		return (1);
	}
	return (0);
}

// #include <stdio.h>

// int	main(int argc, char **argv)
// {
// 	if (argc == 2)
// 	{
// 		printf("%d", ft_isalnum(*argv[1]));
// 	}
// }