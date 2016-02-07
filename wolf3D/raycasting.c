/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/30 15:56:09 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/07 14:46:41 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
static int	get_wall_color(int sx, int sy, int side)
{
	int color;

	color = 0xFFFFF;
	if (side == 0 && sx > 0)
		color = 0xFF0000;
	else if (side == 0 && sx < 0)
		color = 0x0000FF;
	else if (side == 1 && sy > 0)
		color = 0x00FF00;
	else if (side == 1 && sy < 0)
		color = 0xFFFF00;
	return (color);
}
static void	init_dda(t_dda *dda)
{
	dda->delta.x = sqrt(1 + (dda->dir.y * dda->dir.y) /
			(dda->dir.x * dda->dir.x));
	dda->delta.y = sqrt(1 + (dda->dir.x * dda->dir.x) /
			(dda->dir.y * dda->dir.y));
	if (dda->dir.x < 0)
	{
		dda->step.x = -1.0;
		dda->side.x = (dda->x - (double)dda->mapcoord.x) * dda->delta.x;
	}
	else
	{
		dda->step.x = 1.0;
		dda->side.x = ((double)dda->mapcoord.x + 1.0 - dda->x) * dda->delta.x;
	}
	if (dda->dir.y < 0)
	{
		dda->step.y = -1.0;
		dda->side.y = (dda->y - (double)dda->mapcoord.y) * dda->delta.y;
	}
	else
	{
		dda->step.y = 1.0;
		dda->side.y = ((double)dda->mapcoord.y + 1.0 - dda->y) * dda->delta.y;
	}
}

static void	ft_dda(t_dda *dda, t_map *map)
{
	dda->mapcoord.x = (int)dda->x;
	dda->mapcoord.y = (int)dda->y;
	init_dda(dda);
	while (dda->mapcoord.x < map->width && dda->mapcoord.y < map->height &&
			dda->mapcoord.x > -1 && dda->mapcoord.y > -1)
	{
		if (dda->side.x < dda->side.y)
		{
			dda->side.x += dda->delta.x;
			dda->mapcoord.x += dda->step.x;
			dda->sidehit = 0;
		}
		else
		{
			dda->side.y += dda->delta.y;
			dda->mapcoord.y += dda->step.y;
			dda->sidehit = 1;
		}
		if (map->map[dda->mapcoord.x][dda->mapcoord.y].z != 0)
			break ;
	}
	dda->walldist = dda->sidehit == 0 ? fabs((dda->mapcoord.x - dda->x +
				(1 - dda->step.x) / 2) / dda->dir.x) : fabs((dda->mapcoord.y -
					dda->y + (1 - dda->step.y) / 2) / dda->dir.y);
}

static void	draw_wall_slice(t_map *map, t_dda *dda, int i)
{
	double	height;
	t_point	pt[2];
	int		j;

	j = 0;
	height = fabs((double)HEIGHT / dda->walldist);
	pt[0].x = i;
	pt[0].y = HEIGHT / 2 - height / 2;
	if (pt[0].y < 0 || pt[0].y > HEIGHT)
		pt[0].y = 0;
	pt[1].y = HEIGHT / 2 + height / 2;
	if (pt[1].y < 0 || pt[1].y > HEIGHT)
		pt[1].y = HEIGHT - 1;
	pt[1].x = pt[0].x;
	while (j < abs(pt[0].y - pt[1].y))
	{
		pixel_put(map, pt[0].x, pt[0].y + j, get_wall_color(dda->step.x,
					dda->step.y, dda->sidehit));
		j++;
	}
}

void		raycasting(t_map *map)
{
	int		i;
	double	camx;
	t_dda	dda;

	i = 0;
	while (i < WIDTH)
	{
		dda.y = map->player.pos.y;
		dda.x = map->player.pos.x;
		camx = (double)(2.0 * i / WIDTH - 1);
		dda.dir.x = map->player.dir.x + map->plane.x * camx;
		dda.dir.y = map->player.dir.y + map->plane.y * camx;
		ft_dda(&dda, map);
		draw_wall_slice(map, &dda, i);
		i++;
	}
}
