/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:16:41 by vnieto-j          #+#    #+#             */
/*   Updated: 2024/11/19 17:03:28 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *string, size_t n)
{
	char			*tabstring;
	unsigned int	i;

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