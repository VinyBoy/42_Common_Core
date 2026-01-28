/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:33:32 by viny              #+#    #+#             */
/*   Updated: 2025/03/05 16:51:54 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/Libft/include/libft.h"
# include "../mlx_linux/mlx.h"
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <float.h>

# define SIZE 1000

# define SCROLL_UP 4
# define SCROLL_DOWN 5
# define ON_DESTROY 17

typedef struct s_fractal
{
	char	*name;
	void	*mlx;
	void	*window;
	void	*image;
	void	*pointer_to_image;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		x;
	int		y;
	int		color;
	int		max_iteration;
	double	zx;
	double	zy;
	double	cx;
	double	cy;
	double	offset_x;
	double	offset_y;
	double	zoom;
}			t_fractal;

/*Initialisation*/
void	init_fractal(t_fractal *fractal);
int		init_mlx(t_fractal *fractal);

/*Gestion d'event clavier et sourie*/
int		key_hook(int keysym, t_fractal *fractal);
int		mouse_hook(int mouse_code, int x, int y, t_fractal *fractal);

/*zoom*/
void	zoom(t_fractal *fractal, int x, int y, int zoom);

/*Mandelbrot*/
void	calculate_mandelbrot(t_fractal *fractal);

/*Julia*/
void	calculate_julia(t_fractal *fractal, double cx, double cy);
void	set_random_julia(double *cx, double *cy);
double	generate_random_c(void);

/*Burning_ship*/
double	ft_fabs(double x);
void	calculate_burning_ship(t_fractal *fractal);

/*utils*/
void	put_color_to_pixel(t_fractal *fractal, int x, int y, int color);
void	change_iterations(t_fractal *fractal, int keysym);
int		exit_fractal(t_fractal *fractal);

/*main*/
void	ft_avalaible(t_fractal *fractal);
int		draw_fractal(t_fractal *fractal, char *name, double cx, double cy);
int		check_name(const char *name);

#endif