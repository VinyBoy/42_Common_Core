/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:17:59 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/07/17 11:27:04 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	rotate_camera(t_exec *exec, double rot)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = exec->player.dir_x;
	exec->player.dir_x = exec->player.dir_x * cos(rot) - exec->player.dir_y
		* sin(rot);
	exec->player.dir_y = old_dir_x * sin(rot) + exec->player.dir_y
		* cos(rot);
	old_plane_x = exec->player.plane_x;
	exec->player.plane_x = exec->player.plane_x * cos(rot)
		- exec->player.plane_y * sin(rot);
	exec->player.plane_y = old_plane_x * sin(rot) + exec->player.plane_y
		* cos(rot);
}

int	mouse_hook(int x, int y, t_exec *exec)
{
	int				center_x;
	static int		last_x = -1;
	int				diff_x;
	double			rot_speed;

	(void)y;
	center_x = exec->win_width / 2;
	rot_speed = 0.002;
	diff_x = x - last_x;
	last_x = x;
	if (diff_x != 0)
		rotate_camera(exec, diff_x * rot_speed);
	if (x < exec->win_width * 0.2 || x > exec->win_width * 0.8)
	{
		mlx_mouse_move(exec->mlx, exec->win, center_x, exec->win_height / 2);
		last_x = center_x;
	}
	return (0);
}

int	key_hook(int keysym, t_exec *exec)
{
	if (keysym == XK_Escape)
		free_exit(exec, 0);
	if (keysym == XK_w || keysym == XK_W)
		move_forward(exec);
	else if (keysym == XK_s || keysym == XK_S)
		move_backward(exec);
	else if (keysym == XK_a || keysym == XK_A)
		move_left(exec);
	else if (keysym == XK_d || keysym == XK_D)
		move_right(exec);
	else if (keysym == XK_Left)
		rotate(exec, -ROT_SPEED);
	else if (keysym == XK_Right)
		rotate(exec, ROT_SPEED);
	else if (keysym == XK_m || keysym == XK_M)
		exec->show_minimap = !exec->show_minimap;
	return (1);
}

int	handle_window_close(t_exec *exec)
{
	free_exit(exec, 0);
	return (0);
}
