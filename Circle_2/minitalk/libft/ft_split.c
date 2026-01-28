/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 15:44:27 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/01/07 19:12:00 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countword(const char *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			word++;
			while (s[i] != c && s[i])
			{
				i++;
			}
		}
		else
			i++;
	}
	return (word);
}

static int	ft_size_word(const char *s, char c, int i)
{
	int	size;

	size = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		size++;
		i++;
	}
	return (size);
}

static void	ft_free(char **s, int j)
{
	while (j-- > 0)
		free (s[j]);
	free (s);
}

char	**ft_split(const char *s, char c)
{
	char	**dest;
	int		i;
	int		j;
	int		word;
	int		size;

	i = 0;
	j = -1;
	word = ft_countword(s, c);
	dest = (char **)malloc(sizeof(char *) * (word + 1));
	if (dest == NULL)
		return (NULL);
	while (++j < word)
	{
		while (s[i] == c && s[i])
			i++;
		size = ft_size_word(s, c, i);
		dest[j] = ft_substr(s, i, size);
		if (dest[j] == NULL)
			ft_free(dest, j);
		i = i + size;
	}
	dest[j] = NULL;
	return (dest);
}

// #include <stdio.h>

// int	main()
// {
// 	char dest[] = "salut comment ca va ";
//     ft_split(dest, ' ');
// 	printf("%d\n", ft_countword(" salut ca va comment ", ' '));
// 	printf("%d\n", ft_size_word(" salut ca va comment ", ' ', 1));
// }