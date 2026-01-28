/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:17:23 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/07/16 23:32:52 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_exec_exit(t_exec *exec)
{
	free_all_textures(exec);
	if (exec->mlx)
	{
		if (exec->image)
			mlx_destroy_image(exec->mlx, exec->image);
		if (exec->win)
			mlx_destroy_window(exec->mlx, exec->win);
		mlx_destroy_display(exec->mlx);
		free(exec->mlx);
	}
	exit(1);
}

void	free_texture(t_exec *exec, t_texture_mlx *texture)
{
	if (!texture)
		return ;
	if (texture->image && exec->mlx)
		mlx_destroy_image(exec->mlx, texture->image);
	free(texture);
}

void	free_all_textures(t_exec *exec)
{
	if (!exec->assets)
		return ;
	free_texture(exec, exec->assets->north);
	free_texture(exec, exec->assets->south);
	free_texture(exec, exec->assets->east);
	free_texture(exec, exec->assets->west);
	exec->assets->north = NULL;
	exec->assets->south = NULL;
	exec->assets->east = NULL;
	exec->assets->west = NULL;
}

void	free_texture_init(t_exec *exec)
{
	if (exec->assets)
	{
		if (exec->assets->north)
			free(exec->assets->north);
		if (exec->assets->south)
			free(exec->assets->south);
		if (exec->assets->east)
			free(exec->assets->east);
		if (exec->assets->west)
			free(exec->assets->west);
	}
}
