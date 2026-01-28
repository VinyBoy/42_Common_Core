/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 19:39:12 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/04/09 12:06:20 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*def;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = start;
	if (start >= ft_strlen(s))
	{
		def = (char *)malloc(sizeof(char) * 1);
		if (def == NULL)
			return (NULL);
		*def = '\0';
		return (def);
	}
	if (len < ft_strlen(s) - start)
		def = (char *)malloc(sizeof(char) * len + 1);
	else
		def = (char *)malloc(sizeof(char) * ft_strlen(s) - start + 1);
	if (def == NULL)
		return (NULL);
	while (i < len && s[i] != '\0')
		def[i++] = s[j++];
	def[i] = '\0';
	return (def);
}

// #include <stdio.h>

// int main()
// {
// 	printf("%s\n", ft_substr("salut", 2, 4));
// 	return (0);
// }
