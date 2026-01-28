/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:36:59 by viny              #+#    #+#             */
/*   Updated: 2025/07/17 14:01:31 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_ray(t_exec *exec, t_ray *r)
{
	r->camera_x = 2 * exec->the_x / (double)exec->win_width - 1;
	r->ray_dir_x = exec->player.dir_x
		+ exec->player.plane_x * r->camera_x;
	r->ray_dir_y = exec->player.dir_y
		+ exec->player.plane_y * r->camera_x;
	r->map_x = (int)exec->player.x;
	r->map_y = (int)exec->player.y;
	r->delta_dist_x = fabs(1 / r->ray_dir_x);
	r->delta_dist_y = fabs(1 / r->ray_dir_y);
	init_steps(exec, r);
}

void	init_steps(t_exec *exec, t_ray *r)
{
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (exec->player.x - r->map_x)
			* r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - exec->player.x)
			* r->delta_dist_x;
	}
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (exec->player.y - r->map_y)
			* r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - exec->player.y)
			* r->delta_dist_y;
	}
}

void	clear_image(t_exec *exec)
{
	mlx_destroy_image(exec->mlx, exec->image);
	exec->image = mlx_new_image(exec->mlx, exec->win_width, exec->win_height);
	exec->img_data = mlx_get_data_addr(exec->image, &exec->bpp,
			&exec->size_line, &exec->endian);
}
