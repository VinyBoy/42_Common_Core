/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:48:02 by oztozdem          #+#    #+#             */
/*   Updated: 2025/07/15 16:48:27 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	get_minimap_size(t_exec *exec)
{
	int	needed_width;
	int	needed_height;
	int	needed_size;
	int	max_screen_size;

	needed_width = exec->assets->map_width * MINIMAP_SCALE;
	needed_height = exec->assets->map_height * MINIMAP_SCALE;
	if (needed_width > needed_height)
		needed_size = needed_width;
	else
		needed_size = needed_height;
	max_screen_size = exec->win_width * 0.25;
	if (needed_size < MINIMAP_MIN_SIZE)
		return (MINIMAP_MIN_SIZE);
	if (needed_size > MINIMAP_MAX_SIZE || needed_size > max_screen_size)
	{
		if (MINIMAP_MAX_SIZE < max_screen_size)
			return (MINIMAP_MAX_SIZE);
		else
			return (max_screen_size);
	}
	return (needed_size);
}

void	draw_minimap_pixel(t_exec *exec, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_SCALE)
	{
		j = 0;
		while (j < MINIMAP_SCALE)
		{
			if (x + i < exec->win_width && y + j < exec->win_height)
				put_pixel(exec, x + i, y + j, color);
			j++;
		}
		i++;
	}
}
