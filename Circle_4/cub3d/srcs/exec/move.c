/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:40:11 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/07/16 23:39:07 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	move_forward(t_exec *exec)
{
	double	new_x;
	double	new_y;

	new_x = exec->player.x + exec->player.dir_x * MOVE_SPEED;
	new_y = exec->player.y + exec->player.dir_y * MOVE_SPEED;
	if (exec->map[(int)exec->player.y][(int)new_x] != '1'
		&& exec->map[(int)exec->player.y][(int)new_x] != 'X')
		exec->player.x = new_x;
	if (exec->map[(int)new_y][(int)exec->player.x] != '1'
		&& exec->map[(int)new_y][(int)exec->player.x] != 'X')
		exec->player.y = new_y;
}

void	move_backward(t_exec *exec)
{
	double	new_x;
	double	new_y;

	new_x = exec->player.x - exec->player.dir_x * MOVE_SPEED;
	new_y = exec->player.y - exec->player.dir_y * MOVE_SPEED;
	if (exec->map[(int)exec->player.y][(int)new_x] != '1'
		&& exec->map[(int)exec->player.y][(int)new_x] != 'X')
		exec->player.x = new_x;
	if (exec->map[(int)new_y][(int)exec->player.x] != '1'
		&& exec->map[(int)new_y][(int)exec->player.x] != 'X')
		exec->player.y = new_y;
}

void	move_left(t_exec *exec)
{
	double	new_x;
	double	new_y;

	new_x = exec->player.x - exec->player.plane_x * MOVE_SPEED;
	new_y = exec->player.y - exec->player.plane_y * MOVE_SPEED;
	if (exec->map[(int)exec->player.y][(int)new_x] != '1'
		&& exec->map[(int)exec->player.y][(int)new_x] != 'X')
		exec->player.x = new_x;
	if (exec->map[(int)new_y][(int)exec->player.x] != '1'
		&& exec->map[(int)new_y][(int)exec->player.x] != 'X')
		exec->player.y = new_y;
}

void	move_right(t_exec *exec)
{
	double	new_x;
	double	new_y;

	new_x = exec->player.x + exec->player.plane_x * MOVE_SPEED;
	new_y = exec->player.y + exec->player.plane_y * MOVE_SPEED;
	if (exec->map[(int)exec->player.y][(int)new_x] != '1'
		&& exec->map[(int)exec->player.y][(int)new_x] != 'X')
		exec->player.x = new_x;
	if (exec->map[(int)new_y][(int)exec->player.x] != '1'
		&& exec->map[(int)new_y][(int)exec->player.x] != 'X')
		exec->player.y = new_y;
}

void	rotate(t_exec *exec, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = exec->player.dir_x;
	exec->player.dir_x = exec->player.dir_x * cos(angle) - exec->player.dir_y
		* sin(angle);
	exec->player.dir_y = old_dir_x * sin(angle) + exec->player.dir_y
		* cos(angle);
	old_plane_x = exec->player.plane_x;
	exec->player.plane_x = exec->player.plane_x * cos(angle)
		- exec->player.plane_y * sin(angle);
	exec->player.plane_y = old_plane_x * sin(angle) + exec->player.plane_y
		* cos(angle);
}
