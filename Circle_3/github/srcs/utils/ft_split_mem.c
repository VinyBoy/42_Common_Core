/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:21:27 by oztozdem          #+#    #+#             */
/*   Updated: 2025/05/21 14:27:26 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_sep(char str, char c)
{
	if (c == '\0')
		return (0);
	if (str == c)
		return (1);
	else
		return (0);
}

static int	count_words(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (is_sep(str[i], c))
		i++;
	while (str[i])
	{
		while (str[i] && !is_sep(str[i], c))
			i++;
		if (is_sep(str[i], c) || str[i] == '\0')
			count++;
		while (str[i] && is_sep(str[i], c))
			i++;
	}
	return (count);
}

static int	wordlen(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && !is_sep(str[i], c))
		i++;
	return (i);
}

char	**ft_split_mem(char const *s, char c)
{
	char	**p;
	int		i;
	int		j;
	int		k;

	p = mem_manager(MALLOC, sizeof(char *) * (count_words(s, c) + 1), 0);
	if (!p)
		return (NULL);
	i = -1;
	k = 0;
	while (++i < count_words(s, c))
	{
		while (is_sep(s[k], c))
			k++;
		j = -1;
		p[i] = mem_manager(MALLOC, sizeof(char) * (wordlen(s + k, c) + 1), 0);
		if (!p[i])
			return (NULL);
		while (s[k] && !is_sep(s[k], c))
			p[i][++j] = s[k++];
		p[i][++j] = '\0';
		j = k;
	}
	p[i] = NULL;
	return (p);
}
