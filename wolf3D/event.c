/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 11:54:41 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/20 12:04:09 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				expose_hook(t_map *map)
{
	draw(map);
	return (1);
}

static	void	escape(t_map *map)
{
	mlx_destroy_window(map->e.mlx, map->e.win);
	//system("killall afplay");
	free_map(map);
}

int				key_hook(int keycode, t_map *map)
{
	if (!map->pause)
	{
		if (keycode == KEY_W)
			map->key.forward = 0;
		if (keycode == KEY_S)
			map->key.behind = 0;
		if (keycode == KEY_A)
			map->key.left = 0;
		if (keycode == KEY_D)
			map->key.right = 0;
		if (keycode == KEY_LEFT)
			map->key.turn_left = 0;
		if (keycode == KEY_RIGHT)
			map->key.turn_right = 0;
	}
	if (keycode == KEY_ESC)
		escape(map);
	if (keycode == KEY_P)
	{
		map->pause = map->pause == 1 ? 0 : 1;
		draw(map);
	}
	return (1);
}

int				key_press(int keycode, t_map *map)
{
	if (!map->pause)
	{
		if (keycode == KEY_W)
			map->key.forward = 1;
		if (keycode == KEY_S)
			map->key.behind = 1;
		if (keycode == KEY_A)
			map->key.left = 1;
		if (keycode == KEY_D)
			map->key.right = 1;
		if (keycode == KEY_LEFT)
			map->key.turn_left = 1;
		if (keycode == KEY_RIGHT)
			map->key.turn_right = 1;
	}
	return (1);
}

void			move(t_map *map)
{
	if (map->key.forward == 1 && !collision(map, 1))
	{
		map->player.pos.x += map->player.dir.x * 0.1;
		map->player.pos.y += map->player.dir.y * 0.1;
		draw(map);
	}
	if (map->key.behind == 1 && !collision(map, 2))
	{
		map->player.pos.x -= map->player.dir.x * 0.1;
		map->player.pos.y -= map->player.dir.y * 0.1;
		draw(map);
	}
	if (map->key.left == 1 && !collision(map, 3))
	{
		map->player.pos.x += -map->player.dir.y * 0.1;
		map->player.pos.y += map->player.dir.x * 0.1;
		draw(map);
	}
	if (map->key.right == 1 && !collision(map, 4))
	{
		map->player.pos.x -= -map->player.dir.y * 0.1;
		map->player.pos.y -= map->player.dir.x * 0.1;
		draw(map);
	}
}
