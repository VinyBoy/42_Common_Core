/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_texture_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 22:19:15 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/07/17 13:56:07 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	init_texture(t_exec *exec)
{
	exec->assets->north = malloc(sizeof(t_texture_mlx));
	if (!exec->assets->north)
		return (free_texture_init(exec), 0);
	exec->assets->east = malloc(sizeof(t_texture_mlx));
	if (!exec->assets->east)
		return (free_texture_init(exec), 0);
	exec->assets->west = malloc(sizeof(t_texture_mlx));
	if (!exec->assets->west)
		return (free_texture_init(exec), 0);
	exec->assets->south = malloc(sizeof(t_texture_mlx));
	if (!exec->assets->south)
		return (free_texture_init(exec), 0);
	ft_memset(exec->assets->north, 0, sizeof(t_texture_mlx));
	ft_memset(exec->assets->east, 0, sizeof(t_texture_mlx));
	ft_memset(exec->assets->west, 0, sizeof(t_texture_mlx));
	ft_memset(exec->assets->south, 0, sizeof(t_texture_mlx));
	return (1);
}

int	init_mlx_data_addr(t_exec *exec)
{
	exec->assets->north->img_data = mlx_get_data_addr
		(exec->assets->north->image,
			&exec->assets->north->bpp, &exec->assets->north->size_line,
			&exec->assets->north->endian);
	exec->assets->south->img_data = mlx_get_data_addr
		(exec->assets->south->image,
			&exec->assets->south->bpp, &exec->assets->south->size_line,
			&exec->assets->south->endian);
	exec->assets->east->img_data = mlx_get_data_addr(exec->assets->east->image,
			&exec->assets->east->bpp, &exec->assets->east->size_line,
			&exec->assets->east->endian);
	exec->assets->west->img_data = mlx_get_data_addr(exec->assets->west->image,
			&exec->assets->west->bpp, &exec->assets->west->size_line,
			&exec->assets->west->endian);
	exec->assets->north->win_width = exec->assets->img_width;
	exec->assets->north->win_height = exec->assets->img_height;
	exec->assets->south->win_width = exec->assets->img_width;
	exec->assets->south->win_height = exec->assets->img_height;
	exec->assets->east->win_width = exec->assets->img_width;
	exec->assets->east->win_height = exec->assets->img_height;
	exec->assets->west->win_width = exec->assets->img_width;
	exec->assets->west->win_height = exec->assets->img_height;
	return (1);
}

int	init_convert_file_to_xpm(t_exec *exec)
{
	exec->assets->north->image = mlx_xpm_file_to_image(exec->mlx,
			exec->assets->path_no, &exec->assets->img_width,
			&exec->assets->img_height);
	if (!exec->assets->north->image)
		return (free_all_textures(exec),
			error("Error\nCan't load north texture\n"), 0);
	exec->assets->south->image = mlx_xpm_file_to_image(exec->mlx,
			exec->assets->path_so, &exec->assets->img_width,
			&exec->assets->img_height);
	if (!exec->assets->south->image)
		return (free_all_textures(exec),
			error("Error\nCan't load south texture\n"), 0);
	exec->assets->east->image = mlx_xpm_file_to_image(exec->mlx,
			exec->assets->path_ea, &exec->assets->img_width,
			&exec->assets->img_height);
	if (!exec->assets->east->image)
		return (free_all_textures(exec),
			error("Error\nCan't load east texture\n"), 0);
	exec->assets->west->image = mlx_xpm_file_to_image(exec->mlx,
			exec->assets->path_we, &exec->assets->img_width,
			&exec->assets->img_height);
	if (!exec->assets->west->image)
		return (free_all_textures(exec),
			error("Error\nCan't load west texture\n"), 0);
	return (1);
}

int	set_img(t_exec *exec)
{
	if (!init_texture(exec))
		return (error("Error\nMalloc error texture\n"), 0);
	if (!init_convert_file_to_xpm(exec))
		return (0);
	if (!init_mlx_data_addr(exec))
		return (free_all_textures(exec),
			error("Error\nBad get_data_addr_mlx_to_texture"), 0);
	return (1);
}

void	*choose_texture_img(t_exec *exec, t_ray *r)
{
	if (r->side == 0)
	{
		if (r->ray_dir_x > 0)
			return (exec->assets->west->image);
		else
			return (exec->assets->east->image);
	}
	else
	{
		if (r->ray_dir_y > 0)
			return (exec->assets->north->image);
		else
			return (exec->assets->south->image);
	}
}
