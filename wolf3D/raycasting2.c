/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/20 15:03:32 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/20 17:01:58 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	init_ground(t_map *map, t_dda *dda)
{
	if (dda->sidehit == 0 && dda->dir.x > 0)
	{
		map->ground.x = (double)dda->mapcoord.x;
		map->ground.y = (double)dda->mapcoord.y + dda->wallhit;
	}
	else if(dda->sidehit == 0 && dda->dir.x < 0)
	{
		map->ground.x = (double)dda->mapcoord.x + 1.0;
		map->ground.y = (double)dda->mapcoord.y + dda->wallhit;
	}
	else if(dda->sidehit == 1 && dda->dir.y > 0)
	{
		map->ground.x = (double)dda->mapcoord.x + dda->wallhit;
		map->ground.y = (double)dda->mapcoord.y;
	}
	else
	{
		map->ground.x = (double)dda->mapcoord.x + dda->wallhit;
		map->ground.y = (double)dda->mapcoord.y + 1.0;
	}
}

void		floorcasting(t_map *map, t_dda *dda, t_point p)
{

	double		i;
	t_ground	gr;

	init_ground(map, dda);
	if (p.y < 0)
		p.y = HEIGHT;
	i = (double)p.y + 1.0;
	while (i < HEIGHT)
	{
		gr.currentdist = HEIGHT / (2.0 * i - HEIGHT);
		gr.weight = gr.currentdist / dda->walldist;
		gr.currentfloor.x = gr.weight * map->ground.x + (1.0 - gr.weight) *
			dda->x;
		gr.currentfloor.y = gr.weight * map->ground.y + (1.0 - gr.weight) *
			dda->y;
		gr.tex.x = (int)(gr.currentfloor.x * 64) % 64;
		gr.tex.y = (int)(gr.currentfloor.y * 64) % 64;
		printf("x %d y %d\n", gr.tex.x, gr.tex.y);
		pixel_put(map, p.x, i, map->wood[gr.tex.y][gr.tex.x]);
		pixel_put(map, p.x, HEIGHT - i,map->sky[gr.tex.y][gr.tex.x]);
		i++;
	}
}
