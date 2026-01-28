/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:38:21 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/07/28 15:51:40 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	ft_avalaible(t_fractal *fractal)
{
	ft_putendl_fd("Available fractals: Mandelbrot, Julia, Ship", 1);
	exit_fractal(fractal);
}

int	draw_fractal(t_fractal *fractal, char *name, double cx, double cy)
{
	fractal->x = 0;
	fractal->y = 0;
	while (fractal->x < SIZE)
	{
		while (fractal->y < SIZE)
		{
			if (ft_strcmp(name, "Mandelbrot") == 0)
				calculate_mandelbrot(fractal);
			else if (ft_strcmp(name, "Julia") == 0)
				calculate_julia(fractal, cx, cy);
			else if (ft_strcmp(name, "Ship") == 0)
				calculate_burning_ship(fractal);
			else
				ft_avalaible(fractal);
			fractal->y++;
		}
		fractal->x++;
		fractal->y = 0;
	}
	mlx_put_image_to_window(fractal->mlx, fractal->window, fractal->image, 0,
		0);
	return (0);
}

int	check_name(const char *name)
{
	return (ft_strcmp(name, "Mandelbrot") == 0
		|| ft_strcmp(name, "Julia") == 0
		|| ft_strcmp(name, "Ship") == 0);
}

int	main(int argc, char **argv)
{
	t_fractal	*fractal;

	if (argc != 2 || !check_name(argv[1]))
	{
		ft_printf("Usage : ./fractol <fractal>\n");
		ft_printf("Params Available -> Mandelbrot / Julia / Ship\n");
		return (0);
	}
	fractal = malloc(sizeof(t_fractal));
	if (fractal == NULL)
		exit_fractal(fractal);
	init_fractal(fractal);
	if (!init_mlx(fractal))
		exit_fractal(fractal);
	draw_fractal(fractal, argv[1], -0.745429, 0.65);
	mlx_key_hook(fractal->window, key_hook, fractal);
	mlx_mouse_hook(fractal->window, mouse_hook, fractal);
	mlx_hook(fractal->window, 17, 0L, exit_fractal, fractal);
	mlx_loop(fractal->mlx);
	return (0);
}
