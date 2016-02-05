/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/30 15:56:09 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/05 12:50:14 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static	void	init_dda(t_dda *dda)
{
	dda->mapcoord.x = (int)dda->x;
	dda->mapcoord.y = (int)dda->y;
	dda->delta.x = sqrt(1 + dda->dir.y * dda->dir.y) / (dda->dir.x * dda->dir.x);
	dda->delta.y = sqrt(1 + dda->dir.x * dda->dir.x) / (dda->dir.y * dda->dir.y);
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

static	void	ft_dda(t_dda *dda, t_map *map)
{
	init_dda(dda);
	while (dda->mapcoord.x < map->width && dda->mapcoord.y < map->height && dda->mapcoord.x >= 0 && dda->mapcoord.y >=0)
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
		if (map->map[dda->mapcoord.x][dda->mapcoord.y].z > 0)
			break ;
	}
	if (dda->sidehit == 0)
		dda->walldist = fabs(((double)dda->mapcoord.x - dda->x +
					(1 - (double)dda->step.x) / 2) / dda->dir.x);
	else
		dda->walldist = fabs(((double)dda->mapcoord.y - dda->y +
					(1 - (double)dda->step.y) / 2) / dda->dir.y);
}

static void	draw_wall_slice(t_map *map, t_dda *dda, int i)
{
	int	height;
	t_point	pt[2];

	height = abs((int)HEIGHT / (int)dda->walldist);
	pt[0].x = i;
	pt[0].y = -height / 2 + HEIGHT / 2;
	pt[0].y = pt[0].y < 0 ? 0 : pt[0].y;
	pt[1].y = height / 2 + HEIGHT / 2;
	pt[1].y = pt[1].y >= HEIGHT ? HEIGHT - 1 : pt[1].y;
	pt[1].x = pt[0].x;
	printf("height: %d\n", height);
	draw_line(pt[0], pt[1], map);

}

void	raycasting(t_map *map)
{
	int		i;
	double	camX;
	t_dda	dda;

	i = 0;
	while (i < WIDTH)
	{
		dda.y = map->player.pos.y;
		dda.x = map->player.pos.x;
		camX = (double)(2.0 * (double)i / WIDTH - 1);
		dda.dir.x = map->player.dir.x + map->plane.x * camX;
		dda.dir.y = map->player.dir.y + map->plane.y * camX;
		ft_dda(&dda, map);
		printf("walldist: %f\n", dda.walldist);
		draw_wall_slice(map, &dda, i);
		i++;
	}
}
