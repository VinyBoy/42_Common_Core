/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:16:18 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/07/17 14:03:58 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	put_pixel(t_exec *exec, int x, int y, int color)
{
	char	*dst;

	dst = exec->img_data + (y * exec->size_line + x * (exec->bpp / 8));
	*(unsigned int *)dst = color;
}

int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	draw_column(t_exec *exec, t_ray *r)
{
	int			line_height;
	int			draw_start;
	int			draw_end;
	t_tex_info	tex_info;

	line_height = (int)(exec->win_height / r->perp_wall_dist);
	draw_start = -line_height / 2 + exec->win_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + exec->win_height / 2;
	if (draw_end >= exec->win_height)
		draw_end = exec->win_height - 1;
	tex_info.line_height = line_height;
	tex_info.y = draw_start;
	tex_info.end = draw_end;
	draw_textured_wall(exec, &tex_info, r);
}

void	draw_textured_wall(t_exec *exec, t_tex_info *tex_info, t_ray *r)
{
	t_texture_mlx	*texture;

	texture = get_wall_texture(exec, r);
	if (!texture || !texture->img_data)
		return ;
	tex_info->tex_x = get_tex_x(exec, texture, r);
	tex_info->step = 1.0 * texture->win_height / tex_info->line_height;
	tex_info->tex_pos = (tex_info->y - exec->win_height / 2
			+ tex_info->line_height / 2) * tex_info->step;
	draw_wall_line(exec, texture, tex_info, r);
}

void	draw_wall_line(t_exec *exec, t_texture_mlx *texture, t_tex_info *tex,
		t_ray *r)
{
	int	tex_y;
	int	color;

	while (tex->y < tex->end)
	{
		tex_y = (int)tex->tex_pos & (texture->win_height - 1);
		tex->tex_pos += tex->step;
		color = *(int *)(texture->img_data + (tex_y * texture->size_line
					+ tex->tex_x * (texture->bpp / 8)));
		if (r->side == 1)
			color = (color >> 1) & 8355711;
		put_pixel(exec, exec->the_x, tex->y, color);
		tex->y++;
	}
}
