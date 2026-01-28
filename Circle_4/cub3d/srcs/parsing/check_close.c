/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 10:47:28 by oztozdem          #+#    #+#             */
/*   Updated: 2025/07/17 14:11:59 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	wall_or_void(char c)
{
	return (c == '1' || c == ' ');
}

int	check_left_right_borders(char **map, int map_height)
{
	int	line_len;
	int	i;

	i = -1;
	while (++i < map_height)
	{
		line_len = ft_strlen(map[i]);
		if (line_len > 0)
		{
			if (!wall_or_void(map[i][0]))
				return (error("Error\nMap not closed\n"), 0);
			if (!wall_or_void(map[i][line_len - 1]))
				return (error("Error\nMap not closed\n"), 0);
		}
	}
	return (1);
}

int	check_borders(char **map)
{
	int	i;
	int	map_height;

	i = 0;
	if (!map || !map[0])
		return (error("Error\nEmpty map\n"), 0);
	while (map[i])
		i++;
	map_height = i;
	i = -1;
	while (map[0][++i])
		if (!wall_or_void(map[0][i]))
			return (error("Error\nMap not closed\n"), 0);
	i = -1;
	while (map[map_height - 1][++i])
		if (!wall_or_void(map[map_height - 1][i]))
			return (error("Error\nMap not closed\n"), 0);
	if (!check_left_right_borders(map, map_height))
		return (0);
	return (1);
}

int	check_closed_two(char **map, int i, int j, int map_height)
{
	if (map[i][j] == '0')
	{
		if (i > 0 && map[i - 1][j] == 'X')
			return (error("Error\nMap not closed\n"), 0);
		if (i < map_height - 1 && map[i + 1][j] == 'X')
			return (error("Error\nMap not closed\n"), 0);
		if (j > 0 && map[i][j - 1] == 'X')
			return (error("Error\nMap not closed\n"), 0);
		if (map[i][j + 1] && map[i][j + 1] == 'X')
			return (error("Error\nMap not closed\n"), 0);
	}
	return (1);
}

int	check_closed(char **map)
{
	int	i;
	int	j;
	int	map_height;

	map_height = 0;
	while (map[map_height])
		map_height++;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			if (!check_closed_two(map, i, j, map_height))
				return (0);
	}
	return (1);
}
