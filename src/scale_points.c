/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_points.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalbento <lalbento@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:59:49 by lalbento          #+#    #+#             */
/*   Updated: 2025/04/27 16:14:37 by lalbento         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static double	get_z_factor(t_map *map_data)
{
	double	dif_z;
	double	z_factor;

	dif_z = map_data->max_z - map_data->min_z;
	if (dif_z < 5)
		z_factor = 0.7;
	else if (dif_z < 20)
		z_factor = 0.5;
	else if (dif_z < 100)
		z_factor = 0.3;
	else
		z_factor = 0.1;
	return (z_factor);
}

void	scale_points(int *i, int *j, int *z, t_map *map_data)
{
	double	scale;
	double	scaled_z;
	double	z_factor;

	z_factor = get_z_factor(map_data);
	scale = get_scale(map_data);
	*i = (int)((double)*i * scale);
	*j = (int)((double)*j * scale);
	scaled_z = ((double)*z - (map_data->max_z + map_data->min_z) / 2.0)
		* (scale * z_factor);
	*z = (int)scaled_z;
}

static double	get_min(double x, double y)
{
	double	min;

	if (x > y)
		min = y;
	else
		min = x;
	return (min);
}

double	get_scale(t_map *map_data)
{
	double	scale_x;
	double	scale_y;
	double	scale;

	scale_x = (MAP_WIDTH - (MARGIN * 2))
		/ ((map_data->width + map_data->heigth) * cos(M_PI / 6));
	scale_y = (MAP_HEIGTH - (MARGIN * 2))
		/ ((map_data->width + map_data->heigth) * sin(M_PI / 6));
	scale = get_min(scale_x, scale_y);
	return (scale * 0.8);
}
