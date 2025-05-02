/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalbento <lalbento@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:56:04 by lalbento          #+#    #+#             */
/*   Updated: 2025/04/27 17:16:40 by lalbento         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define MAP_HEIGTH 1080
# define MAP_WIDTH 1920
# define MARGIN 200
# define M_PI 3.14159265358979323846
# define ESCAPE 65307
# define UP 65362 
# define DOWN 65364
# define LEFT 65363
# define RIGHT 65361

# include "../Libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <math.h>
# include <unistd.h>

typedef struct s_map
{
	int		heigth;
	int		width;
	int		min_z;
	int		max_z;
	char	**data;
	char	**data2;
}	t_map;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct s_line
{
	t_point	*a;
	t_point	*b;
	char	**data;
	char	**extra_data;
}	t_line;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	void	*img;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	*addr;
	int	angle;
}	t_vars;

// parsing
int		get_heigth(char *filename);
int		get_width(char **map);
int		get_maxz(char **map);
int		get_minz(char **map);
char	**get_map(char *filename, int size);
t_map	*get_data(char **map);

// drawing
void	slope_greater_than_one(t_vars *vars, int dx,
			int dy, t_line *line);
void	slope_less_than_one(t_vars *vars, int dx,
			int dy, t_line *line);
void	draw_line(t_vars *vars, t_line *line);
void	draw_grid_x(t_vars *vars, t_map *map_data, char **map);
void	draw_grid_y(t_vars *vars, t_map *map_data, char **map);

// transform
t_point	*get_point(int i, int j, char **extra_data, t_map *map_data, t_vars *vars);
void	scale_points(int *i, int *j, int *z, t_map *map_data);
void	isometric(int *x, int *y, int z, int angle_index);
double	get_scale(t_map *map_data);

//colors
int		interpolate_color(int color1, int color2, int d, int i);
int		get_color(int height, t_map *map_data);

//minilibx
int		key_pressed(int keycode, t_vars *vars);
int		close_program(t_vars *vars);
int		key_hook(int keycode, t_map *map_data);
int 	key_hook_2(int keycode, t_vars *vars);

//utils
int		ft_atoi_hex(char *str);
int		get_direction(int x1, int x2);
void	free_matrix(char **matrix);
void	swap(t_point *a, t_point *b);
void	put_pixel_to_image(t_vars *vars, int x, int y, int color);

#endif
