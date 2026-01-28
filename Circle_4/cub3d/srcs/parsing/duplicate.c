/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:54:45 by oztozdem          #+#    #+#             */
/*   Updated: 2025/07/14 13:34:25 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_texture_duplicates(t_assets *assets, char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
	{
		if (assets->no_count > 0)
			return (0);
		assets->no_count++;
	}
	else if (!ft_strncmp(line, "SO ", 3))
	{
		if (assets->so_count > 0)
			return (0);
		assets->so_count++;
	}
	else if (!ft_strncmp(line, "WE ", 3))
	{
		if (assets->we_count > 0)
			return (0);
		assets->we_count++;
	}
	else if (!ft_strncmp(line, "EA ", 3))
	{
		if (assets->ea_count > 0)
			return (0);
		assets->ea_count++;
	}
	return (1);
}

int	check_color_duplicates(t_assets *assets, char *line)
{
	if (!ft_strncmp(line, "F ", 2))
	{
		if (assets->f_count > 0)
			return (0);
		assets->f_count++;
	}
	else if (!ft_strncmp(line, "C ", 2))
	{
		if (assets->c_count > 0)
			return (0);
		assets->c_count++;
	}
	return (1);
}

int	check_all_textures_present(t_assets *assets)
{
	if (assets->no_count != 1 || assets->so_count != 1 || assets->we_count != 1
		|| assets->ea_count != 1)
		return (error("Error\nMissing texture(s)\n"), 0);
	if (assets->f_count != 1 || assets->c_count != 1)
		return (error("Error\nMissing color(s)\n"), 0);
	return (1);
}

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}
