/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:58:53 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/07/17 14:13:56 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *source, size_t size)
{
	size_t		i;
	char		*tabdest;
	char		*tabsource;

	if (!dest || !source)
		return (NULL);
	i = 0;
	tabdest = (char *) dest;
	tabsource = (char *) source;
	while (i < size)
	{
		tabdest[i] = tabsource[i];
		i++;
	}
	return (tabdest);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	char test[6] = "Salut";
// 	char test2[6] = "Pomme";
// 	printf("%p\n", ft_memcpy(test, test2, 5));
// 	printf("%p\n", memcpy(test, test2, 5));
// 	return (0);
// }