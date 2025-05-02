/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalbento <lalbento@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:45:51 by lalbento          #+#    #+#             */
/*   Updated: 2025/04/27 15:28:25 by lalbento         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	free_line(t_line *line)
{
	free_matrix(line->data);
	free_matrix(line->extra_data);
	free(line->a);
	free(line->b);
	free(line);
}

static t_line	*fill_line_data_y(t_map *map_data, int j)
{
	t_line	*line;

	line = malloc(sizeof(t_line));
	if (!line)
		return (NULL);
	line->data = ft_split(map_data->data[j], ',');
	line->extra_data = ft_split(map_data->data2[j], ',');
	return (line);
}

static t_line	*fill_line_data_x(t_map *map_data, int j)
{
	t_line	*line;

	line = malloc(sizeof(t_line));
	if (!line)
		return (NULL);
	line->data = ft_split(map_data->data[j], ',');
	line->extra_data = ft_split(map_data->data[j + 1], ',');
	return (line);
}

void	draw_grid_y(t_vars *vars, t_map *map_data, char **map)
{
	int		i;
	int		j;
	t_line	*line;

	i = 0;
	while (map[i] && i < map_data->heigth - 1)
	{
		map_data->data = ft_split(map[i], ' ');
		map_data->data2 = ft_split(map[i + 1], ' ');
		j = 0;
		while (map_data->data2[j])
		{
			line = fill_line_data_y(map_data, j);
			line->a = get_point(i, j, line->data, map_data, vars);
			line->b = get_point(i + 1, j, line->extra_data, map_data, vars);
			draw_line(vars, line);
			free_line(line);
			j++;
		}
		free_matrix(map_data->data2);
		free_matrix(map_data->data);
		i++;
	}
}

void	draw_grid_x(t_vars *vars, t_map *map_data, char **map)
{
	int		i;
	int		j;
	t_line	*line;

	i = 0;
	while (map[i])
	{
		j = 0;
		map_data->data = ft_split(map[i], ' ');
		while (j < map_data->width - 1)
		{
			line = fill_line_data_x(map_data, j);
			line->a = get_point(i, j, line->data, map_data, vars);
			line->b = get_point(i, j + 1, line->extra_data, map_data, vars);
			draw_line(vars, line);
			free_line(line);
			j++;
		}
		free_matrix(map_data->data);
		i++;
	}
}
