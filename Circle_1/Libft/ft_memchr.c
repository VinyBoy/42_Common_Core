/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:16:41 by vnieto-j          #+#    #+#             */
/*   Updated: 2024/11/20 15:00:47 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *memoryblock, int searchedchar, size_t size)
{
	size_t			i;
	unsigned char	*tabmemoryblock;
	unsigned char	thechar;

	i = 0;
	tabmemoryblock = (unsigned char *) memoryblock;
	thechar = (unsigned char)searchedchar;
	while (size > 0)
	{
		if (tabmemoryblock[i] == thechar)
			return (tabmemoryblock + i);
		i++;
		size--;
	}
	return (NULL);
}
