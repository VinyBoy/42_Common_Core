/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 12:09:56 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/07/21 12:37:59 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup(const char *source)
{
	char	*dest;
	int		i;

	i = 0;
	while (source[i] != '\0')
	{
		i++;
	}
	dest = (char *) malloc (sizeof(*dest) * i + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (source[i] != '\0')
	{
		dest[i] = source[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
