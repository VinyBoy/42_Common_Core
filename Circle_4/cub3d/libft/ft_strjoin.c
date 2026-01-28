/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 19:09:43 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/01/07 19:10:02 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*def;
	int		i;
	int		j;

	i = 0;
	def = (char *)malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2)+ 1);
	if (def == NULL)
		return (NULL);
	while (s1[i])
	{
		def[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		def[i] = s2[j];
		i++;
		j++;
	}
	def[i] = '\0';
	return (def);
}

// #include <stdio.h>

// int main()
// {
// 	printf("%s\n", ft_strjoin("bonjour", "salut"));
// }