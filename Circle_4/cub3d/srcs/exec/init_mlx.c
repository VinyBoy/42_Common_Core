/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:16:48 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/07/17 13:40:21 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	init_mlx(t_exec *exec)
{
	exec->mlx = mlx_init();
	if (!exec->mlx)
		return (0);
	if (!init_new_window(exec))
		return (0);
	if (!init_set_image(exec))
		return (0);
	if (!init_new_image(exec))
		return (0);
	exec->img_data = mlx_get_data_addr(exec->image, &exec->bpp,
			&exec->size_line, &exec->endian);
	mlx_hook(exec->win, 6, 1L << 6, mouse_hook, exec);
	mlx_hook(exec->win, 2, 1L << 0, key_hook, exec);
	mlx_hook(exec->win, 17, 0, handle_window_close, exec);
	mlx_put_image_to_window(exec->mlx, exec->win, exec->image, 0, 0);
	mlx_loop_hook(exec->mlx, render_frame, exec);
	mlx_loop(exec->mlx);
	return (1);
}

int	init_new_window(t_exec *exec)
{
	exec->win = mlx_new_window(exec->mlx, exec->win_width, exec->win_height,
			"cub3D");
	if (!exec->win)
	{
		mlx_destroy_display(exec->mlx);
		free(exec->mlx);
		return (0);
	}
	return (1);
}

int	init_set_image(t_exec *exec)
{
	if (!set_img(exec))
	{
		mlx_destroy_window(exec->mlx, exec->win);
		mlx_destroy_display(exec->mlx);
		free(exec->mlx);
		return (0);
	}
	return (1);
}

int	init_new_image(t_exec *exec)
{
	exec->image = mlx_new_image(exec->mlx, exec->win_width, exec->win_height);
	if (!exec->image)
	{
		free_all_textures(exec);
		mlx_destroy_window(exec->mlx, exec->win);
		mlx_destroy_display(exec->mlx);
		free(exec->mlx);
		return (0);
	}
	return (1);
}
