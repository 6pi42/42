/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/30 15:56:09 by cboyer            #+#    #+#             */
/*   Updated: 2016/01/31 14:23:30 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	raycasting(t_map *map)
{
	int	i;
	t_ray	ray;

	i = 0;
	while (i < WIDTH)
	{
		ray.camx = 2 * i / WIDTH - 1;
		ray.posx = map->cam.x;
		ray.posy = map->cam.y;
		ray.dirx = map->dir_perso.dx + map->cam.plane.dx * map->cam.x;
		ray.diry = map->dir_perso.dy + map->cam.plane.dy * map->cam.y;
		
	}
}
