/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/24 15:05:59 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/11 14:15:00 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_hook(int keycode, t_map *map)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(map->e.mlx, map->e.win);
		exit(0);
	}
	if (keycode == 35)
	{
		map->c = map->c ? 0 : 1;
		draw(map);
	}
	if (keycode == 126)
		map->key.backward = 0;
	if (keycode == 125)
		map->key.forward = 0;
	if (keycode == 123)
		map->key.right = 0;
	if (keycode == 124)
		map->key.left = 0;
	return (1);
}

int	key_press(int keycode, t_map *map)
{
	if (keycode == 126)
		map->key.backward = 1;
	if (keycode == 125)
		map->key.forward = 1;
	if (keycode == 123)
		map->key.right = 1;
	if (keycode == 124)
		map->key.left = 1;
	return (0);
}

int	motion_notify(int x, int y, t_map *map)
{
	if (x < WIDTH && y < HEIGHT && x >= 0 && y >= 0)
	{
		if (!ft_strcmp(map->mode, "julia"))
		{
			map->julia.i = 1.5 * (y - map->mouse.y / 2) /
				(map->zoom * HEIGHT / 2);
			map->julia.r = 1.5 * (x - map->mouse.x / 2) /
				(map->zoom * WIDTH / 2);
			draw(map);
		}
		if ((!ft_strcmp(map->mode, "mandelbrot") ||
					!ft_strcmp(map->mode, "rabbit") ||
					!ft_strcmp(map->mode, "siegel") ||
					!ft_strcmp(map->mode, "burning_ship")) && y != 0)
		{
			map->max_iter = 2 * HEIGHT / y;
			draw(map);
		}
	}
	return (0);
}

int	expose_hook(t_map *map)
{
	draw(map);
	return (1);
}

int	buttonpress_hook(int button, int x, int y, t_map *map)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		if (button == 5 || button == 1)
			map->zoom *= 1.3;
		if (button == 4 || button == 2)
			map->zoom /= 1.3;
		draw(map);
	}
	return (0);
}
