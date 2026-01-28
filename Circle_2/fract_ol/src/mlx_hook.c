/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:50:35 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/07/20 15:22:56 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	zoom(t_fractal *fractal, int x, int y, int zoom)
{
	double	zoom_level;

	zoom_level = 1.42;
	if (zoom == 1)
	{
		fractal->offset_x = (x / fractal->zoom + fractal->offset_x) - (x
				/ (fractal->zoom * zoom_level));
		fractal->offset_y = (y / fractal->zoom + fractal->offset_y) - (y
				/ (fractal->zoom * zoom_level));
		fractal->zoom *= zoom_level;
	}
	else if (zoom == -1)
	{
		fractal->offset_x = (x / fractal->zoom + fractal->offset_x) - (x
				/ (fractal->zoom / zoom_level));
		fractal->offset_y = (y / fractal->zoom + fractal->offset_y) - (y
				/ (fractal->zoom / zoom_level));
		fractal->zoom /= zoom_level;
	}
	else
		return ;
}

int	key_hook(int keysym, t_fractal *fractal)
{
	double	cx;
	double	cy;

	cx = fractal->cx;
	cy = fractal->cy;
	if (keysym == XK_Escape)
		exit_fractal (fractal);
	else if (keysym == XK_Left)
		fractal->offset_x -= 42 / fractal->zoom;
	else if (keysym == XK_Right)
		fractal->offset_x += 42 / fractal->zoom;
	else if (keysym == XK_Up)
		fractal->offset_y -= 42 / fractal->zoom;
	else if (keysym == XK_Down)
		fractal->offset_y += 42 / fractal->zoom;
	else if (keysym == XK_r)
		init_fractal(fractal);
	else if (keysym == XK_c)
		fractal->color += (255 * 255 * 255) / 100;
	else if (keysym == XK_j)
		set_random_julia(&cx, &cy);
	draw_fractal(fractal, fractal->name, cx, cy);
	return (0);
}

int	mouse_hook(int mouse_code, int x, int y, t_fractal *fractal)
{
	if (mouse_code == ON_DESTROY)
		exit_fractal(fractal);
	else if (mouse_code == SCROLL_UP)
		zoom(fractal, x, y, 1);
	else if (mouse_code == SCROLL_DOWN)
		zoom(fractal, x, y, -1);
	draw_fractal(fractal, fractal->name, fractal->cx, fractal->cy);
	return (0);
}
