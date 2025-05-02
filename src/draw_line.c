/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalbento <lalbento@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:45:51 by lalbento          #+#    #+#             */
/*   Updated: 2025/04/27 15:28:54 by lalbento         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	slope_greater_than_one(t_vars *vars, int dx, int dy, t_line *line)
{
	int	p;
	int	i;
	int	sx;
	int	sy;
	int	color;

	i = 0;
	p = 2 * dy - dx;
	sx = get_direction(line->a->x, line->b->x);
	sy = get_direction(line->a->y, line->b->y);
	while (i <= dy)
	{
		color = interpolate_color(line->a->color, line->b->color, dy, i);
		put_pixel_to_image(vars, line->a->x, line->a->y, color);
		line->a->y += sy;
		if (p < 0)
			p += 2 * dx;
		else
		{
			line->a->x += sx;
			p += 2 * dx - 2 * dy;
		}
		i++;
	}
}

void	slope_less_than_one(t_vars *vars, int dx, int dy, t_line *line)
{
	int	p;
	int	i;
	int	sx;
	int	sy;
	int	color;

	i = 0;
	p = 2 * dy - dx;
	sx = get_direction(line->a->x, line->b->x);
	sy = get_direction(line->a->y, line->b->y);
	while (i <= dx)
	{
		color = interpolate_color(line->a->color, line->b->color, dx, i);
		put_pixel_to_image(vars, line->a->x, line->a->y, color);
		line->a->x += sx;
		if (p < 0)
			p = p + 2 * dy;
		else
		{
			line->a->y += sy;
			p = p + 2 * dy - 2 * dx;
		}
		i++;
	}
}

static int	ft_abs(int n)
{
	if (n < 0)
		return (n * (-1));
	else
		return (n);
}


void	draw_line(t_vars *vars, t_line *line)
{
	int	dx;
	int	dy;

	dx = ft_abs(line->b->x - line->a->x);
	dy = ft_abs(line->b->y - line->a->y);
	if (ft_abs(dy) <= ft_abs(dx))
	{
		if (line->a->x > line->b->x)
			swap(line->a, line->b);
		slope_less_than_one(vars, dx, dy, line);
	}
	else
	{
		if (line->a->y > line->b->y)
			swap(line->a, line->b);
		slope_greater_than_one(vars, dx, dy, line);
	}
}
