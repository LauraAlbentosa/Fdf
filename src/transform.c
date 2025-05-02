/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalbento <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:38:05 by lalbento          #+#    #+#             */
/*   Updated: 2025/04/27 15:46:35 by lalbento         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric(int *x, int *y, int z, int angle_index)
{
	double	angle;
	int		prev_x;
	int		prev_y;

	angle = M_PI/angle_index; //para manejar las rotaciones creo que lo suyo es hacer 
	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) * cos(angle);
	*y = (prev_x + prev_y) * sin(angle) - z;
}

static void	point_data(t_point *point, char **extra_data, t_map *map_data)
{
	if (!extra_data[1])
		point->color = get_color(ft_atoi(extra_data[0]), map_data);
	else
		point->color = ft_atoi_hex(extra_data[1]);
}

t_point	*get_point(int i, int j, char **extra_data, t_map *map_data, t_vars *vars)
{
	t_point	*point;
	int		x;
	int		y;
	int		z;
	double	scale;

	point = malloc(sizeof(t_point));
	if (!point)
		return (NULL);
	z = ft_atoi(extra_data[0]);
	x = j - ((map_data->width - 1) / 2);
	y = i - ((map_data->heigth - 1) / 2);
	scale_points(&i, &j, &z, map_data);
	scale = get_scale(map_data);
	x *= (int)scale;
	y *= (int)scale;
	isometric(&x, &y, z, vars->angle);
	x += MAP_WIDTH / 2;
	y += MAP_HEIGTH / 2;
	point_data(point, extra_data, map_data);
	point->x = x;
	point->y = y;
	return (point);
}
