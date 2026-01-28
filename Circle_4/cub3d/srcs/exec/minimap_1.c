/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:27:12 by oztozdem          #+#    #+#             */
/*   Updated: 2025/07/15 16:48:25 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_minimap_border(t_exec *exec)
{
	int	i;
	int	actual_width;
	int	actual_height;

	actual_width = exec->assets->map_width * MINIMAP_SCALE;
	actual_height = exec->assets->map_height * MINIMAP_SCALE;
	i = 0;
	while (i < actual_width + 4)
	{
		put_pixel(exec, MINIMAP_X - 2 + i, MINIMAP_Y - 2, 0x00FFFFFF);
		put_pixel(exec, MINIMAP_X - 2 + i, MINIMAP_Y + actual_height + 1,
			0x00FFFFFF);
		i++;
	}
	i = 0;
	while (i < actual_height + 4)
	{
		put_pixel(exec, MINIMAP_X - 2, MINIMAP_Y - 2 + i, 0x00FFFFFF);
		put_pixel(exec, MINIMAP_X + actual_width + 1, MINIMAP_Y - 2 + i,
			0x00FFFFFF);
		i++;
	}
}

void	draw_minimap_background(t_exec *exec)
{
	int	x;
	int	y;
	int	actual_width;
	int	actual_height;

	actual_width = exec->assets->map_width * MINIMAP_SCALE;
	actual_height = exec->assets->map_height * MINIMAP_SCALE;
	y = 0;
	while (y < actual_height)
	{
		x = 0;
		while (x < actual_width)
		{
			put_pixel(exec, MINIMAP_X + x, MINIMAP_Y + y, 0x00000000);
			x++;
		}
		y++;
	}
}

void	draw_player_on_minimap(t_exec *exec)
{
	int	player_x;
	int	player_y;
	int	i;
	int	j;
	int	minimap_size;

	minimap_size = get_minimap_size(exec);
	i = -2;
	player_x = MINIMAP_X + (exec->player.x * MINIMAP_SCALE);
	player_y = MINIMAP_Y + (exec->player.y * MINIMAP_SCALE);
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			if (player_x + i >= MINIMAP_X && player_x + i < MINIMAP_X
				+ minimap_size && player_y + j >= MINIMAP_Y && player_y
				+ j < MINIMAP_Y + minimap_size)
				put_pixel(exec, player_x + i, player_y + j, 0x00FF0000);
			j++;
		}
		i++;
	}
}

void	draw_minimap_map(t_exec *exec)
{
	int	map_x;
	int	map_y;
	int	minimap_size;

	minimap_size = get_minimap_size(exec);
	map_y = 0;
	while (map_y < exec->assets->map_height && map_y
		* MINIMAP_SCALE < minimap_size)
	{
		map_x = 0;
		while (exec->map[map_y][map_x] && map_x * MINIMAP_SCALE < minimap_size)
		{
			if (exec->map[map_y][map_x] == '1'
				|| exec->map[map_y][map_x] == 'X')
				draw_minimap_pixel(exec, MINIMAP_X + map_x * MINIMAP_SCALE,
					MINIMAP_Y + map_y * MINIMAP_SCALE, 0x00404040);
			else if (exec->map[map_y][map_x] == '0'
				|| is_player_char(exec->map[map_y][map_x])
				|| exec->map[map_y][map_x] == 'V')
				draw_minimap_pixel(exec, MINIMAP_X + map_x * MINIMAP_SCALE,
					MINIMAP_Y + map_y * MINIMAP_SCALE, 0x00C0C0C0);
			map_x++;
		}
		map_y++;
	}
}

void	draw_minimap(t_exec *exec)
{
	if (!exec->show_minimap)
		return ;
	draw_minimap_background(exec);
	draw_minimap_border(exec);
	draw_minimap_map(exec);
	draw_player_on_minimap(exec);
}
