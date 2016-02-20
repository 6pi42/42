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
		map->ground.x = dda->mapcoord.x;
		map->ground.y = dda->mapcoord.y + dda->wallhit;
	}
	else if(dda->sidehit == 0 && dda->dir.x < 0)
	{
		map->ground.x = dda->mapcoord.x + 1.0;
		map->ground.y = dda->mapcoord.y + dda->wallhit;
	}
	else if(dda->sidehit == 1 && dda->dir.y > 0)
	{
		map->ground.x = dda->mapcoord.x + dda->wallhit;
		map->ground.y = dda->mapcoord.y;
	}
	else
	{
		map->ground.x = dda->mapcoord.x + dda->wallhit;
		map->ground.y = dda->mapcoord.y + 1.0;
	}
}

static void		draw_ground_slice(t_map *map, t_dda *dda, t_point *p)
{

	int			i;
	t_ground	gr;

	init_ground(map, dda);
	gr.walldist = dda->walldist;
	gr.playerdist = 0.0;
	if (p[1].y < 0)
		p[1].y = HEIGHT;
	i = p[1].y + 1;
	while (i < HEIGHT)
	{
		gr.currentdist = (double)HEIGHT / (2.0 * (double)i - (double)HEIGHT);
		gr.weight = (gr.currentdist - gr.playerdist) / (gr.walldist - gr.playerdist);
		gr.currentfloor.x = gr.weight * map->ground.x + (1.0 - gr.weight) * (double)dda->x;
		gr.currentfloor.y = gr.weight * map->ground.y + (1.0 - gr.weight) * (double)dda->y;
		gr.tex.x = (int)(gr.currentfloor.x * 64) % 64;
		gr.tex.y = (int)(gr.currentfloor.y * 64) % 64;
		pixel_put(map, p[0].x, i, map->wood[gr.tex.x][gr.tex.y]);
		i++;
	}
}

void		draw_sky_floor(t_map *map, t_dda *dda,t_point p1, t_point p2)
{
	int		i;
	t_point	p[2];

	p[0] = p1;
	p[1] = p2;
	i = 0;
	while (i < p1.y)
	{
		pixel_put(map, p1.x, i, SKY);
		i++;
	}
	draw_ground_slice(map, dda, p);
	i = HEIGHT;
/*	while (i > p2.y)
	{
		pixel_put(map, p1.x, i, FLOOR);
		i--;
	}*/
}
