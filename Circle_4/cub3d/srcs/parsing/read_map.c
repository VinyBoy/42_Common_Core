/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:43:59 by oztozdem          #+#    #+#             */
/*   Updated: 2025/07/17 14:07:50 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	process_line(t_assets *assets, char *line)
{
	char	*c_line;
	int		result;

	c_line = clean_line(line);
	if (!c_line)
		return (0);
	if (is_texture(c_line))
		result = handle_textures(assets, c_line);
	else if (is_color(c_line))
		result = handle_colors(assets, c_line);
	else if (is_map(line))
		result = handle_map(assets, line);
	else if (assets->map_started)
		result = 2;
	else
		result = (error("Error\nInvalid line in file\n"), 0);
	free(c_line);
	return (result);
}

int	process_current_line(t_assets *assets, char *line)
{
	int	result;

	if (line[0] == '\n' || line[0] == '\0')
		return (handle_empty_line(assets));
	result = process_line(assets, line);
	return (result);
}

int	read_map(t_assets *assets)
{
	char	*line;
	int		result;

	line = get_next_line(assets->fd);
	while (line)
	{
		result = process_current_line(assets, line);
		free(line);
		if (result == 0)
			return (0);
		if (result == 2)
			break ;
		line = get_next_line(assets->fd);
	}
	return (1);
}
