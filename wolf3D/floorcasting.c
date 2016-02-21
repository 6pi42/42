/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorcasting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 11:40:38 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/21 13:38:47 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	init_ground(t_dda *dda, t_ground *gr)
{
	if (dda->sidehit == 0 && dda->dir.x > 0)
	{
		gr->pos.x = (double)dda->mapcoord.x;
		gr->pos.y = (double)dda->mapcoord.y + dda->wallhit;
	}
	else if (dda->sidehit == 0 && dda->dir.x < 0)
	{
		gr->pos.x = (double)dda->mapcoord.x + 1.0;
		gr->pos.y = (double)dda->mapcoord.y + dda->wallhit;
	}
	else if (dda->sidehit == 1 && dda->dir.y > 0)
	{
		gr->pos.x = (double)dda->mapcoord.x + dda->wallhit;
		gr->pos.y = (double)dda->mapcoord.y;
	}
	else
	{
		gr->pos.x = (double)dda->mapcoord.x + dda->wallhit;
		gr->pos.y = (double)dda->mapcoord.y + 1.0;
	}
}

void		floorcasting(t_map *map, t_dda *dda, t_point p)
{
	double		i;
	t_ground	gr;

	init_ground(dda, &gr);
	if (p.y < 0)
		p.y = HEIGHT;
	i = (double)p.y;
	while (i < HEIGHT)
	{
		gr.currentdist = HEIGHT / (2.0 * i - HEIGHT);
		gr.weight = gr.currentdist / dda->walldist;
		gr.currentfloor.x = gr.weight * gr.pos.x + (1.0 - gr.weight) *
			map->player.pos.x;
		gr.currentfloor.y = gr.weight * gr.pos.y + (1.0 - gr.weight) *
			map->player.pos.y;
		gr.tex.x = (int)(gr.currentfloor.x * 64) % 64;
		gr.tex.y = (int)(gr.currentfloor.y * 64) % 64;
		pixel_put(map, p.x, i, map->tex[3][gr.tex.y][gr.tex.x]);
		pixel_put(map, p.x, HEIGHT - i, map->tex[0][gr.tex.y][gr.tex.x]);
		i++;
	}
}
