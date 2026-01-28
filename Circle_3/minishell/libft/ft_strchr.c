/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:17:55 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/01/07 16:04:39 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int searchedchar)
{
	char	*s;

	s = (char *)str;
	while (*s != (char)searchedchar)
	{
		if (*s == '\0')
		{
			return (NULL);
		}
		s++;
	}
	return (s);
}

//  #include <stdio.h>

//  int	main()
//  {
//  	char *test = "Bastien et emilie";	
//  	printf("%s", ft_strchr(test, 'i'));
//  }