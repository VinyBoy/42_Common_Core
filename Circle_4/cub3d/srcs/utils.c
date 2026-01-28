/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:46:13 by oztozdem          #+#    #+#             */
/*   Updated: 2025/07/07 12:10:10 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	error(char *msg)
{
	int	i;

	i = 0;
	write(2, "\033[1;31m", 7);
	while (msg[i])
	{
		write(2, &msg[i], 1);
		i++;
	}
	write(2, "\033[0m", 4);
}

int	c_strchr(char *str, char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (str[i] == '\0' && s[j] == '\0')
		return (1);
	while (str[i])
	{
		while (str[i + j] == s[j] && str[i + j] && s[j])
			j++;
		if (s[j] == '\0' && str[i + j] == '\0')
			return (1);
		else
			j = 0;
		i++;
	}
	return (0);
}
