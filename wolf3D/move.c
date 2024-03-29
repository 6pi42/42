/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 11:55:58 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/20 12:10:14 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				collision(t_map *map, int a)
{
	if (a == 1 && map->map[(int)(map->player.pos.x + map->player.dir.x * 0.1)]
			[(int)(map->player.pos.y + map->player.dir.y * 0.1)].z == 1)
		return (1);
	if (a == 2 && map->map[(int)(map->player.pos.x - map->player.dir.x * 0.1)]
			[(int)(map->player.pos.y - map->player.dir.y * 0.1)].z == 1)
		return (1);
	if (a == 3 && map->map[(int)(map->player.pos.x + (-map->player.dir.y) *
			0.1)][(int)(map->player.pos.y + map->player.dir.x * 0.1)].z == 1)
		return (1);
	if (a == 4 && map->map[(int)(map->player.pos.x - (-map->player.dir.y) *
			0.1)][(int)(map->player.pos.y - map->player.dir.x * 0.1)].z == 1)
		return (1);
	return (0);
}

static	void	rotate_2(t_map *map)
{
	t_vec	tmp;

	tmp = map->player.dir;
	map->player.dir.x = tmp.x * cos(3 * M_PI / 180.0) -
		tmp.y * sin(3 * M_PI / 180.0);
	map->player.dir.y = tmp.x * sin(3 * M_PI / 180.0) +
		tmp.y * cos(3 * M_PI / 180.0);
	tmp = map->plane;
	map->plane.x = tmp.x * cos(3 * M_PI / 180.0) -
		tmp.y * sin(3 * M_PI / 180.0);
	map->plane.y = tmp.x * sin(3 * M_PI / 180.0) +
		tmp.y * cos(3 * M_PI / 180.0);
	draw(map);
}

void			rotate(t_map *map)
{
	t_vec tmp;

	if (map->key.turn_right == 1)
	{
		tmp = map->player.dir;
		map->player.dir.x = tmp.x * cos(-3 * M_PI / 180.0) -
			tmp.y * sin(-3 * M_PI / 180.0);
		map->player.dir.y = tmp.x * sin(-3 * M_PI / 180.0) +
			tmp.y * cos(-3 * M_PI / 180.0);
		tmp = map->plane;
		map->plane.x = tmp.x * cos(-3 * M_PI / 180.0) -
			tmp.y * sin(-3 * M_PI / 180.0);
		map->plane.y = tmp.x * sin(-3 * M_PI / 180.0) +
			tmp.y * cos(-3 * M_PI / 180.0);
		draw(map);
	}
	if (map->key.turn_left == 1)
		rotate_2(map);
}
