/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:08:15 by oztozdem          #+#    #+#             */
/*   Updated: 2025/07/14 11:37:59 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	count_commas(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}

int	is_valid_number(char *str)
{
	int	i;
	int	num;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	num = ft_atoi(str);
	return (num >= 0 && num <= 255);
}

int	parse_color(char *color_str, int *rgb)
{
	char	**split;
	int		i;

	if (count_commas(color_str) != 2)
		return (0);
	split = ft_split(color_str, ',');
	if (!split)
		return (0);
	i = 0;
	while (split[i])
		i++;
	if (i != 3)
		return (free_array(split), 0);
	i = 0;
	while (i < 3)
	{
		if (!is_valid_number(split[i]))
			return (free_array(split), 0);
		rgb[i] = ft_atoi(split[i]);
		i++;
	}
	free_array(split);
	return (1);
}

int	store_color(t_assets *assets, char *line)
{
	char	*color;

	if (line[0] == 'F' && line[1] == ' ')
	{
		color = line + 2;
		if (!parse_color(color, assets->floor))
			return (0);
	}
	else if (line[0] == 'C' && line[1] == ' ')
	{
		color = line + 2;
		if (!parse_color(color, assets->ceiling))
			return (0);
	}
	else
		return (0);
	return (1);
}
