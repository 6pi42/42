/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 11:55:58 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/07 14:26:10 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		collision(t_map *map, int a)
{
	if (a == 1 && map->map[(int)(map->player.pos.x + map->player.dir.x * 0.1)]
			[(int)(map->player.pos.y + map->player.dir.y * 0.1)].z != 0)
		return (1);
	if (a == 2 && map->map[(int)(map->player.pos.x - map->player.dir.x * 0.1)]
			[(int)(map->player.pos.y - map->player.dir.y * 0.1)].z != 0)
		return (1);
	if (a == 3 && map->map[(int)(map->player.pos.x + (-map->player.dir.y) *
			0.1)][(int)(map->player.pos.y + map->player.dir.x * 0.1)].z != 0)
		return (1);
	if (a == 4 && map->map[(int)(map->player.pos.x - (-map->player.dir.y) *
			0.1)][(int)(map->player.pos.y - map->player.dir.x * 0.1)].z != 0)
		return (1);
	return (0);
}
/*
void	rotate(t_map *map)
{
	
}
*/
