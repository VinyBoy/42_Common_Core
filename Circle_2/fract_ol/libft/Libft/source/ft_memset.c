/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:47:52 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/07/21 12:37:36 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memset(void *pointer, int value, size_t count)
{
	size_t	i;
	char	*string;

	i = 0;
	string = (char *) pointer;
	while (i < count)
	{
		string[i] = value;
		i++;
	}
	return (pointer);
}
