/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:37:24 by viny              #+#    #+#             */
/*   Updated: 2025/07/17 14:02:44 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	render_frame(t_exec *exec)
{
	clear_image(exec);
	draw_floor_and_ceiling(exec);
	exec->the_x = 0;
	while (exec->the_x < exec->win_width)
	{
		cast_ray(exec);
		exec->the_x++;
	}
	draw_minimap(exec);
	mlx_put_image_to_window(exec->mlx, exec->win, exec->image, 0, 0);
	return (0);
}

void	draw_floor_and_ceiling(t_exec *exec)
{
	int	x;
	int	y;

	y = -1;
	while (++y < exec->win_height / 2)
	{
		x = -1;
		while (++x < exec->win_width)
			put_pixel(exec, x, y, exec->ceiling_ex);
	}
	y = exec->win_height / 2;
	while (y < exec->win_height)
	{
		x = -1;
		while (++x < exec->win_width)
			put_pixel(exec, x, y, exec->floor_ex);
		y++;
	}
}

void	cast_ray(t_exec *exec)
{
	t_ray	r;

	init_ray(exec, &r);
	perform_dda(exec, &r);
	compute_wall(exec, &r);
	draw_column(exec, &r);
}

void	compute_wall(t_exec *exec, t_ray *r)
{
	if (r->side == 0)
		r->perp_wall_dist = (r->map_x - exec->player.x + (1 - r->step_x) / 2)
			/ r->ray_dir_x;
	else
		r->perp_wall_dist = (r->map_y - exec->player.y + (1 - r->step_y) / 2)
			/ r->ray_dir_y;
	r->line_height = (int)(exec->win_height / r->perp_wall_dist);
	r->draw_start = -r->line_height / 2 + exec->win_height / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + exec->win_height / 2;
	if (r->draw_end >= exec->win_height)
		r->draw_end = exec->win_height - 1;
}

void	perform_dda(t_exec *exec, t_ray *r)
{
	r->hit = 0;
	while (!r->hit)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (exec->map[r->map_y][r->map_x] == '1')
			r->hit = 1;
	}
}
