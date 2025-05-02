/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalbento <lalbento@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:34:02 by lalbento          #+#    #+#             */
/*   Updated: 2025/04/27 16:43:27 by lalbento         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	hooks(t_vars *vars)
{
	mlx_hook(vars->win, 2, 1L << 0, key_hook_2, vars);
	mlx_hook(vars->win, 2, 1L << 0, key_pressed, vars);
	mlx_hook(vars->win, 17, 1L << 17, close_program, vars);
	mlx_loop(vars->mlx);
}
static t_vars	*init_vars(void)
{
	t_vars	*vars;

	vars = malloc(sizeof(t_vars));
	if (!vars)
		return (NULL);
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, MAP_WIDTH, MAP_HEIGTH, "Fdf");
	vars->img = mlx_new_image(vars->mlx, MAP_WIDTH, MAP_HEIGTH);
	vars->addr = mlx_get_data_addr(vars->img,
			&vars->bits_per_pixel, &vars->line_length, &vars->endian);
	vars->angle = 6;
	return (vars);
}

static t_map	*init_map(char *filename, char ***map)
{
	t_map	*map_data;

	map_data = malloc(sizeof(t_map));
	if (!map_data)
		return (NULL);
	map_data->heigth = get_heigth(filename);
	*map = get_map(filename, map_data->heigth);
	if (!map || !map_data->heigth)
	{
		write(2, "format error", 12);
		free(map_data);
		return (NULL);
	}
	map_data->width = get_width(*map);
	map_data->min_z = get_minz(*map);
	map_data->max_z = get_maxz(*map);
	return (map_data);
}

int	main(int argc, char **argv)
{
	t_vars	*vars;
	t_map	*map_data;
	char	**map;

	if (argc != 2 || !argv[1])
	{
		write(2, "format error", 12);
		return (1);
	}
	map_data = init_map(argv[1], &map);
	if (!map_data)
		return (1);
	vars = init_vars();
	draw_grid_x(vars, map_data, map);
	draw_grid_y(vars, map_data, map);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	hooks(vars);
	free_matrix(map);
	free(vars);
	free_matrix(map_data->data);
	free_matrix(map_data->data2);
	free(map_data);
	return (0);
}
