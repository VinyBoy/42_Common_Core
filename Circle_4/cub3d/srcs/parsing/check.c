/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:46:02 by oztozdem          #+#    #+#             */
/*   Updated: 2025/07/23 14:33:16 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	all_info_complete(t_assets *assets)
{
	if (assets->no_count == 1 && assets->so_count == 1 && assets->we_count == 1
		&& assets->ea_count == 1 && assets->f_count == 1
		&& assets->c_count == 1)
		return (1);
	return (0);
}

int	check_map(char **map)
{
	int	i;
	int	j;
	int	count_p;

	i = -1;
	count_p = 0;
	while (map[++i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'N'
				&& map[i][j] != 'S' && map[i][j] != 'E' && map[i][j] != 'W'
				&& map[i][j] != ' ')
				return (error("Error\nInvalid character detected\n"), 0);
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
				count_p++;
			j++;
		}
	}
	if (count_p != 1)
		return (error("Error\nNo or too much player detected\n"), 0);
	return (1);
}

int	check_textures(char **textures)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	if (!textures)
		return (error("Error\nNo textures found\n"), 0);
	while (textures[++i])
	{
		j = 0;
		while (textures[i][j] && textures[i][j] != ' ')
			j++;
		while (textures[i][j] && textures[i][j] == ' ')
			j++;
		if (!textures[i][j])
			return (error("Error\nInvalid texture format\n"), 0);
		len = ft_strlen(&textures[i][j]);
		if (len < 4)
			return (error("Error\nTexture path too short\n"), 0);
		if (ft_strncmp(&textures[i][j + len - 4], ".xpm", 4))
			return (error("Error\nTexture must be .xpm file\n"), 0);
	}
	return (1);
}

int	get_map_width(char *map)
{
	int	width;

	width = 0;
	while (map[width])
		width++;
	return (width);
}
