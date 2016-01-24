/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/24 15:05:59 by cboyer            #+#    #+#             */
/*   Updated: 2016/01/24 15:30:08 by cboyer           ###   ########.fr       */
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
	if (keycode == 24)
		map->zoom += 1;
	if (keycode == 27)
		map->zoom -= 1;
	if (keycode == 126)
		map->mouse.y += 10;
	if (keycode == 125)
		map->mouse.y -= 10;
	if (keycode == 123)
		map->mouse.x += 10;
	if (keycode == 124)
		map->mouse.x -= 10;
	if (keycode == 124 || keycode == 123 || keycode == 125 || keycode == 126
			|| keycode == 27 || keycode == 24)
		draw(map);
	return (1);
}

int	motion_notify(int x, int y, t_map *map)
{
	if (x < WIDTH && y < HEIGHT && x >= 0 && y >= 0 && !ft_strcmp(map->mode ,"julia"))
	{
		map->julia.i = 1.5 * (y - map->mouse.y / 2) / (0.5 * map->zoom * HEIGHT);
		map->julia.r = 1.5 * (x - map->mouse.x / 2) / (0.5 * map->zoom * WIDTH);
		draw(map);
	}
	return (0);
}

int	expose_hook(t_map *map)
{
	draw(map);
	return (1);
}

int	circulate_notify_down(t_map *map)
{
	map->zoom += 1;
	draw(map);
	return (1);
}

int	circulate_notify_up(t_map *map)
{
	map->zoom -= 1;
	draw(map);
	return (1);
}
