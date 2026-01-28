/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:16:41 by vnieto-j          #+#    #+#             */
/*   Updated: 2024/11/20 16:36:19 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

// #include <stdio.h>
// int	main()
// {
//   	char *test = "Bastien et emilie";	
//   	printf("%s", ft_strrchr(test, 'i'));
// }