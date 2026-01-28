/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:48:31 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/01/09 18:26:10 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_char_in_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*str;
	size_t		i;
	size_t		start;
	size_t		end;

	if (!s1)
		return (NULL);
	start = 0;
	while (s1[start] && ft_char_in_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_char_in_set(s1[end - 1], set))
		end--;
	str = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
		str[i++] = s1[start++];
	str[i] = 0;
	return (str);
}

// #include <stdio.h>

// int main()
// {
// 	printf("%d\n", first("   xxx   xxx", " x"));
// 	printf("%d\n", end("   xxx   xxx", " x"));
// 	printf("%s\n", ft_strtrim("   xxx   xxx", " x"));
// 	// printf("%d\n", first("tata", "toto"));
// 	// printf("%d\n", end("tata", "toto"));
// 	// printf("%s\n", ft_strtrim("atototatatoto", "toto"));
// 	//taille de s1  = 13 / taille de set = 3
// 	//strlen de s1 = 12 / strlen de set = 2 
// 	//dest = (char *)malloc(sizeof(char) * ft_strlen(s1)
// 	//		- (first(s1, set) + end(s1, set)) + 1);
// 	// 12 - (11 + 11) + 1
// 	// 12 - 22 + 1 = -9
// }