/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:33:10 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/01/07 18:28:36 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *string, size_t n)
{
	char				*tabstring;
	unsigned int		i;

	tabstring = (char *) string;
	i = 0;
	while (i < n)
	{
		tabstring[i] = '\0';
		i++;
	}
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	tab[5] = "Salut";
// 	int i = 0;
// 	while (i < 5)
// 	{
// 		printf("%c \n", tab[i]);
// 		i++;
// 	}
// 	i = 0;
// 	ft_bzero(tab, 5);
// 	while (i < 5)
// 	{
// 		printf("%c \n", tab[i] + 48);
// 		i++;
// 	}
// }