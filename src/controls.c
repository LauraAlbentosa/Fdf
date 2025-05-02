/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalbento <lalbento@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:51:30 by lalbento          #+#    #+#             */
/*   Updated: 2025/04/27 14:58:17 by lalbento         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_pressed(int keycode, t_vars *vars)
{
	if (keycode == ESCAPE)
		close_program(vars);
	return (0);
}

static void	cleanup_window(t_vars *vars)
{
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
}

static void	cleanup_images(t_vars *vars)
{
	if (vars->img)
		mlx_destroy_image(vars->mlx, vars->img);
}

static void	cleanup_display(t_vars *vars)
{
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
}

int	close_program(t_vars *vars)
{
	cleanup_images(vars);
	cleanup_window(vars);
	cleanup_display(vars);
	exit(0);
}

int key_hook_2(int keycode, t_vars	*vars)
{
	if (keycode == RIGHT) //flecha derecha
		vars->angle = vars->angle + 1;
	else if (keycode == LEFT) //flecha izquierda
		vars->angle = vars->angle - 1;
	printf("%i", vars->angle);
	return (0);
}


