/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:39:23 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/01/07 18:27:10 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *memoryBlock, int searchedChar, size_t size)
{
	size_t			i;
	unsigned char	*tabmemoryblock;
	unsigned char	d;

	i = 0;
	tabmemoryblock = (unsigned char *) memoryBlock;
	d = (unsigned char)searchedChar;
	while (size > 0)
	{
		if (tabmemoryblock[i] == d)
			return (tabmemoryblock + i);
		i++;
		size--;
	}
	return (NULL);
}

// #include <stdio.h>

// int main()
// {
// 	printf("%s", ft_memchr("sAlut", 65, 1));
// }