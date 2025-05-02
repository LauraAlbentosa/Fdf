/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalbento <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:40:45 by lalbento          #+#    #+#             */
/*   Updated: 2025/04/26 14:51:19 by lalbento         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_color(int height, t_map *map_data)
{
	double	ratio;
	t_color	base;
	t_color	top;
	t_color	result;

	base.r = 118;
	base.g = 215;
	base.b = 196;
	top.r = 220;
	top.g = 118;
	top.b = 51;
	if (map_data->max_z == map_data->min_z)
		ratio = 0;
	else
		ratio = (double)(height - map_data->min_z)
			/ (map_data->max_z - map_data->min_z);
	result.r = (int)((1 - ratio) * base.r + ratio * top.r);
	result.g = (int)((1 - ratio) * base.g + ratio * top.g);
	result.b = (int)((1 - ratio) * base.b + ratio * top.b);
	return ((result.r << 16) | (result.g << 8) | result.b);
}

int	interpolate_color(int color1, int color2, int d, int i)
{
	double	t;
	int		r;
	int		g;
	int		b;

	t = (double)i / d;
	r = ((1 - t) * ((color1 >> 16) & 0xFF)) + (t * ((color2 >> 16) & 0xFF));
	g = ((1 - t) * ((color1 >> 8) & 0xFF)) + (t * ((color2 >> 8) & 0xFF));
	b = ((1 - t) * (color1 & 0xFF)) + (t * (color2 & 0xFF));
	return ((r << 16) | (g << 8) | b);
}
