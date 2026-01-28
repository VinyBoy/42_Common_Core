/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:37:09 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/07/17 14:05:47 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_exec	*ft_exec(int argc, char **argv, t_assets *assets)
{
	t_exec	*exec;

	(void)argc;
	(void)argv;
	exec = malloc(sizeof(t_exec));
	if (!exec)
		return (error("Error\nMalloc error on t_exec struct\n"), NULL);
	ft_memset(exec, 0, sizeof(t_exec));
	init_exec(exec, assets);
	if (!init_mlx(exec))
	{
		free_all_textures(exec);
		free(exec);
		return (NULL);
	}
	return (exec);
}

void	init_exec(t_exec *exec, t_assets *assets)
{
	exec->map = assets->map;
	exec->map_width = 30;
	exec->map_height = 14;
	exec->win_height = 800;
	exec->win_width = 1400;
	exec->floor_ex = rgb_to_int(assets->floor[0], assets->floor[1],
			assets->floor[2]);
	exec->ceiling_ex = rgb_to_int(assets->ceiling[0], assets->ceiling[1],
			assets->ceiling[2]);
	exec->assets = assets;
	exec->show_minimap = 0;
	init_pos_player(exec);
}

void	init_pos_player(t_exec *exec)
{
	int	x;
	int	y;

	y = 0;
	while (exec->map[y] != NULL)
	{
		x = 0;
		while (exec->map[y][x] != '\0')
		{
			if (exec->map[y][x] == 'N' || exec->map[y][x] == 'S'
				|| exec->map[y][x] == 'E' || exec->map[y][x] == 'O')
			{
				exec->player.x = x + 0.5;
				exec->player.y = y + 0.5;
				init_dir_plane(exec, x, y);
				return ;
			}
			x++;
		}
		y++;
	}
}

void	init_dir_plane(t_exec *exec, int x, int y)
{
	if (exec->map[y][x] == 'N')
	{
		exec->player.dir_x = 0.0;
		exec->player.dir_y = -1.0;
		exec->player.plane_x = 0.66;
		exec->player.plane_y = 0.0;
	}
	else if (exec->map[y][x] == 'S')
	{
		exec->player.dir_x = 0.0;
		exec->player.dir_y = 1.0;
		exec->player.plane_x = -0.66;
		exec->player.plane_y = 0.0;
	}
	init_dir_plane_ew(exec, x, y);
	return ;
}

void	init_dir_plane_ew(t_exec *exec, int x, int y)
{
	if (exec->map[y][x] == 'E')
	{
		exec->player.dir_x = 1.0;
		exec->player.dir_y = 0.0;
		exec->player.plane_x = 0.0;
		exec->player.plane_y = 0.66;
	}
	else if (exec->map[y][x] == 'O')
	{
		exec->player.dir_x = -1.0;
		exec->player.dir_y = 0.0;
		exec->player.plane_x = 0.0;
		exec->player.plane_y = -0.66;
	}
	return ;
}
