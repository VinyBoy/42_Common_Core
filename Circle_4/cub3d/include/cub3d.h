/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:29:03 by oztozdem          #+#    #+#             */
/*   Updated: 2025/07/17 15:11:54 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define ON_DESTROY 17
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05
# define MINIMAP_MAX_SIZE 300
# define MINIMAP_MIN_SIZE 150
# define MINIMAP_SCALE 8
# define MINIMAP_X 20
# define MINIMAP_Y 20

typedef struct s_tex_info
{
	int				tex_x;
	int				y;
	int				end;
	double			step;
	double			tex_pos;
	int				line_height;
}					t_tex_info;

typedef struct s_texture_mlx
{
	void			*mlx;
	void			*win;
	void			*image;
	char			**map;
	int				win_width;
	int				win_height;
	char			*img_data;
	int				size_line;
	int				bpp;
	int				endian;
}					t_texture_mlx;

typedef struct s_assets
{
	char			**textures;
	char			**map;
	int				floor[3];
	int				ceiling[3];
	int				fd;
	int				no_count;
	int				so_count;
	int				we_count;
	int				ea_count;
	int				f_count;
	int				c_count;
	int				map_started;
	int				map_ended;
	int				t_size;
	int				m_size;
	int				map_height;
	int				map_width;
	int				img_width;
	int				img_height;
	char			*path_no;
	char			*path_so;
	char			*path_ea;
	char			*path_we;
	t_texture_mlx	*north;
	t_texture_mlx	*south;
	t_texture_mlx	*east;
	t_texture_mlx	*west;
}					t_assets;

typedef struct s_player
{
	double			x;
	double			y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
}					t_player;

typedef struct s_ray
{
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
}					t_ray;

typedef struct s_exec
{
	void			*mlx;
	void			*win;
	void			*image;
	char			**map;
	int				win_width;
	int				win_height;
	char			*img_data;
	int				size_line;
	int				bpp;
	int				endian;
	int				floor_ex;
	int				ceiling_ex;
	int				map_width;
	int				map_height;
	int				show_minimap;
	int				the_x;
	t_player		player;
	t_assets		*assets;
}					t_exec;

/*draw.c*/
void				put_pixel(t_exec *exec, int x, int y, int color);
int					rgb_to_int(int r, int g, int b);
void				draw_column(t_exec *exec, t_ray *r);
void				draw_textured_wall(t_exec *exec, t_tex_info *tex_info,
						t_ray *r);
void				draw_wall_line(t_exec *exec, t_texture_mlx *texture,
						t_tex_info *tex, t_ray *r);

/*exec_1.c*/
t_exec				*ft_exec(int argc, char **argv, t_assets *assets);
void				init_exec(t_exec *exec, t_assets *assets);
void				init_pos_player(t_exec *exec);
void				init_dir_plane(t_exec *exec, int x, int y);
void				init_dir_plane_ew(t_exec *exec, int x, int y);

/*free.c*/
void				free_exec_exit(t_exec *exec);
void				free_texture(t_exec *exec, t_texture_mlx *texture);
void				free_all_textures(t_exec *exec);
void				free_texture_init(t_exec *exec);

/*hook.c*/
int					key_hook(int keysym, t_exec *exec);
int					mouse_hook(int x, int y, t_exec *exec);
void				rotate_camera(t_exec *exec, double rot);
int					handle_window_close(t_exec *exec);

/*init_mlx.c*/
int					init_mlx(t_exec *exec);
int					init_new_window(t_exec *exec);
int					init_set_image(t_exec *exec);
int					init_new_image(t_exec *exec);

/* minimap_1.c */
void				draw_minimap_border(t_exec *exec);
void				draw_minimap_background(t_exec *exec);
void				draw_player_on_minimap(t_exec *exec);
void				draw_minimap_map(t_exec *exec);
void				draw_minimap(t_exec *exec);

/* minimap_2.c */
int					get_minimap_size(t_exec *exec);
void				draw_minimap_pixel(t_exec *exec, int x, int y, int color);

/*move.c*/
void				move_forward(t_exec *exec);
void				move_backward(t_exec *exec);
void				move_left(t_exec *exec);
void				move_right(t_exec *exec);
void				rotate(t_exec *exec, double angle);

/*raycasting_1.c*/
int					render_frame(t_exec *exec);
void				draw_floor_and_ceiling(t_exec *exec);
void				cast_ray(t_exec *exec);
void				compute_wall(t_exec *exec, t_ray *r);
void				perform_dda(t_exec *exec, t_ray *r);

/*raycasting_init.c*/
void				init_ray(t_exec *exec, t_ray *r);
void				init_steps(t_exec *exec, t_ray *r);
void				clear_image(t_exec *exec);

/*raycasting_texture_1.c*/
t_texture_mlx		*get_wall_texture(t_exec *exec, t_ray *r);
int					get_tex_x(t_exec *exec, t_texture_mlx *texture, t_ray *r);
int					get_wall_x(t_exec *exec, t_ray *r);

/*raycasting_texture_2.c*/
int					init_texture(t_exec *exec);
int					init_mlx_data_addr(t_exec *exec);
int					init_convert_file_to_xpm(t_exec *exec);
int					set_img(t_exec *exec);
void				*choose_texture_img(t_exec *exec, t_ray *r);

/* parsing/color.c */
int					count_commas(char *str);
int					is_valid_number(char *str);
int					parse_color(char *color_str, int *rgb);
int					store_color(t_assets *assets, char *line);

/* parsing/duplicate.c */
int					check_texture_duplicates(t_assets *assets, char *line);
int					check_color_duplicates(t_assets *assets, char *line);
int					check_all_textures_present(t_assets *assets);
int					is_player_char(char c);

/* parsing/free.c */
void				free_array(char **array);
// void				free_img(t_img *img);
void				free_assets(t_assets *assets);
void				free_visited(char **visited, int i);

/* parsing/check.c */
int					all_info_complete(t_assets *assets);
int					check_map(char **map);
int					check_textures(char **textures);
int					get_map_width(char *map);

/* parsing/parsing.c */
void				copy_with_single_spaces(char *line, char *c_line, int *i,
						int *j);
char				*clean_line(char *line);
char				**line_to_array(char **array, char *line, int *size);
int					read_map(t_assets *assets);
int					parsing(t_assets *assets);
t_assets			*parse_map(char **argv);

/* parsing/print.c */
void				print_array(char **array);
void				print_floor(int tab[3]);
void				print_ceiling(int tab[3]);
void				print_assets(t_assets *assets);

/* parsing/utils.c */
int					is_texture(char *line);
int					is_color(char *line);
int					is_map(char *line);
t_assets			*init_assets(void);
int					is_directory(const char *path);

/* parsing/fill_map.c */
int					get_max_line_len(char **map);
char				*fill_line(char **map, char *line, int line_index,
						int target_length);
char				**fill_map(char **map);

/* parsing/check_close.c */
int					wall_or_void(char c);
int					check_borders(char **map);
int					check_closed(char **map);

/* parsing/v_or_x.c */
char				v_or_x(char **map, int i, int j);
int					get_map_height(char **map);

/* parsing/read_map_utils.c */
int					check_empty_lines_in_map(t_assets *assets);
int					handle_empty_line(t_assets *assets);
int					handle_textures(t_assets *assets, char *c_line);
int					handle_colors(t_assets *assets, char *c_line);
int					handle_map(t_assets *assets, char *line);

/* parsing/img.c */
char				*get_texture_path(char **textures, char *id);
int					set_path(t_assets *assets);
void				mlx_destroy_protected(void *mlx_ptr, void *img_ptr);

/* ./utils.c */
void				error(char *msg);
int					c_strchr(char *str, char *s);

/* ./free.c */
void				free_exit(t_exec *exec, int exit_code);

#endif