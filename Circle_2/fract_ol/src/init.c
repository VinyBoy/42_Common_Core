/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:42:36 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/03/06 12:46:09 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	init_fractal(t_fractal *fractal)
{
	fractal->x = 0;
	fractal->y = 0;
	fractal->color = 0xFCBE11;
	fractal->zoom = 200;
	fractal->offset_x = -3;
	fractal->offset_y = -2;
	fractal->max_iteration = 300;
}

int	init_mlx(t_fractal *fractal)
{
	fractal->mlx = mlx_init();
	if (fractal->mlx == NULL)
		return (0);
	fractal->window = mlx_new_window(fractal->mlx, SIZE, SIZE, "Fract_ol");
	if (fractal->window == NULL)
		return (0);
	fractal->image = mlx_new_image(fractal->mlx, SIZE, SIZE);
	if (fractal->image == NULL)
		return (0);
	fractal->pointer_to_image = mlx_get_data_addr(fractal->image,
			&fractal->bits_per_pixel, &fractal->size_line,
			&fractal->endian);
	if (fractal->pointer_to_image == NULL)
		return (0);
	return (1);
}
