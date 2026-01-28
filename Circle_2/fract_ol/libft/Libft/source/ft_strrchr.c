/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:57:10 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/07/21 12:38:25 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strrchr(const char *str, int searchedchar)
{
	char	*s;
	int		i;

	s = (char *)str;
	i = ft_strlen((str));
	while (i >= 0)
	{
		if (s[i] == (char)searchedchar)
		{
			return (s + i);
		}
		i--;
	}
	return (NULL);
}

//   #include <stdio.h>

//   int	main()
//   {
//   	char *test = "Bastien et emilie";	
//   	printf("%s", ft_strrchr(test, 'i'));
//   }