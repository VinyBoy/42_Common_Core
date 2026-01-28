/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:52:59 by oztozdem          #+#    #+#             */
/*   Updated: 2025/07/17 13:35:18 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_empty_lines_in_map(t_assets *assets)
{
	char	*next_line;

	next_line = get_next_line(assets->fd);
	while (next_line)
	{
		if (next_line[0] != '\n' && next_line[0] != '\0')
		{
			if (is_map(next_line))
				return (free(next_line),
					error("Error\nEmpty line in map\n"), 0);
			else if (is_texture(next_line) || is_color(next_line))
				return (free(next_line),
					error("Error\nTexture/Color found after map start\n"), 0);
			else
				return (free(next_line),
					error("Error\nInvalid content after map\n"), 0);
		}
		free(next_line);
		next_line = get_next_line(assets->fd);
	}
	return (1);
}

int	handle_empty_line(t_assets *assets)
{
	if (assets->map_started)
	{
		if (!check_empty_lines_in_map(assets))
			return (0);
		return (2);
	}
	return (1);
}

int	handle_textures(t_assets *assets, char *c_line)
{
	if (assets->map_started)
		return (error("Error\nTexture found after map start\n"), 0);
	if (!check_texture_duplicates(assets, c_line))
		return (error("Error\nDuplicate texture found\n"), 0);
	assets->textures = line_to_array(assets->textures, c_line, &assets->t_size);
	if (!assets->textures)
		return (0);
	return (1);
}

int	handle_colors(t_assets *assets, char *c_line)
{
	if (assets->map_started)
		return (error("Error\nColor found after map start\n"), 0);
	if (!check_color_duplicates(assets, c_line))
		return (error("Error\nDuplicate color found\n"), 0);
	if (!store_color(assets, c_line))
		return (error("Error\nInvalid color format\n"), 0);
	return (1);
}

int	handle_map(t_assets *assets, char *line)
{
	if (!all_info_complete(assets))
		return (error("Error\nMap found before all assets defined\n"), 0);
	assets->map_started = 1;
	assets->map = line_to_array(assets->map, line, &assets->m_size);
	if (!assets->map)
		return (0);
	return (1);
}
