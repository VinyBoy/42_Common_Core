/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:14:24 by oztozdem          #+#    #+#             */
/*   Updated: 2025/05/29 20:21:59 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strdup_mem(const char *source)
{
	char	*dest;
	int		i;

	i = 0;
	while (source[i] != '\0')
	{
		i++;
	}
	dest = mem_manager(MALLOC, sizeof(*dest) * (i + 1), NULL);
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

char	*ft_strjoin_mem(char *s1, char *s2)
{
	char	*def;
	int		i;
	int		j;

	i = 0;
	def = mem_manager(MALLOC, sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)
				+ 1), NULL);
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

static int	itoa_len(int n)
{
	unsigned int	nb;
	int				count;

	count = 1;
	if (n < 0)
	{
		count++;
		n = n * -1;
	}
	nb = n;
	while (nb > 9)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa_mem(int n)
{
	char			*dest;
	int				lengh;
	unsigned int	nb;

	lengh = itoa_len(n);
	dest = mem_manager(MALLOC, sizeof(char) * (lengh + 1), NULL);
	if (dest == NULL)
		return (NULL);
	dest[lengh--] = '\0';
	if (n == 0)
		dest[0] = '0';
	if (n < 0)
	{
		n = n * -1;
		dest[0] = '-';
	}
	nb = n;
	while (nb > 0)
	{
		dest[lengh] = (nb % 10) + 48;
		nb = nb / 10;
		lengh--;
	}
	return (dest);
}

char	*ft_substr_mem(char const *s, unsigned int start, size_t len)
{
	char			*def;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = start;
	if (start >= ft_strlen(s))
	{
		def = mem_manager(MALLOC, sizeof(char) * 1, NULL);
		if (def == NULL)
			return (NULL);
		*def = '\0';
		return (def);
	}
	if (len < ft_strlen(s) - start)
		def = mem_manager(MALLOC, sizeof(char) * (len + 1), NULL);
	else
		def = mem_manager(MALLOC, sizeof(char) * (ft_strlen(s) - start + 1),
				NULL);
	if (def == NULL)
		return (NULL);
	while (i < len && s[i] != '\0')
		def[i++] = s[j++];
	def[i] = '\0';
	return (def);
}
