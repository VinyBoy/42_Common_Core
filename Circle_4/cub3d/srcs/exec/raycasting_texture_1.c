/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_texture_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:13:19 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/07/23 15:14:08 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_texture_mlx	*get_wall_texture(t_exec *exec, t_ray *r)
{
	if (r->side == 0)
	{
		if (r->ray_dir_x > 0)
			return (exec->assets->west);
		else
			return (exec->assets->east);
	}
	else
	{
		if (r->ray_dir_y > 0)
			return (exec->assets->north);
		else
			return (exec->assets->south);
	}
}

int	get_wall_x(t_exec *exec, t_ray *r)
{
	double	wall_x;

	if (r->side == 0)
		wall_x = exec->player.y + r->perp_wall_dist * r->ray_dir_y;
	else
		wall_x = exec->player.x + r->perp_wall_dist * r->ray_dir_x;
	wall_x -= floor(wall_x);
	return ((int)(wall_x * (double)exec->assets->north->win_width));
}

int	get_tex_x(t_exec *exec, t_texture_mlx *texture, t_ray *r)
{
	int	tex_x;

	tex_x = get_wall_x(exec, r);
	if (r->side == 0 && r->ray_dir_x > 0)
		tex_x = texture->win_width - tex_x - 1;
	if (r->side == 1 && r->ray_dir_y < 0)
		tex_x = texture->win_width - tex_x - 1;
	return (tex_x);
}
