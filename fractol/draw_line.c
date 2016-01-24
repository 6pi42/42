/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 15:21:22 by cboyer            #+#    #+#             */
/*   Updated: 2016/01/24 11:32:56 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		bresenmann_1(t_bres *bres, t_point pt1, t_map *map)
{
	int	i;
	int	y;
	int	x;

	y = pt1.y;
	x = pt1.x;
	i = 0;
	pixel_put(map, x, y, 0xFFFFFF);
	while (i < bres->dx)
	{
		if (bres->e >= 0)
		{
			y += bres->sy;
			bres->e += bres->inc1;
		}
		else
			bres->e += bres->inc2;
		x += bres->sx;
		pixel_put(map, x, y, 0xFFFFFF);
		i++;
	}
}

static void		bresenmann_2(t_bres *bres, t_point pt1, t_map *map)
{
	int	i;
	int	y;
	int	x;

	y = pt1.y;
	x = pt1.x;
	i = 0;
	pixel_put(map, x, y, 0xFFFFFF);
	while (i < bres->dy)
	{
		if (bres->e >= 0)
		{
			x += bres->sx;
			bres->e += bres->inc1;
		}
		else
			bres->e += bres->inc2;
		y += bres->sy;
		pixel_put(map, x , y, 0xFFFFFF);
		i++;
	}
}

static t_bres	*get_bres(t_point pt1, t_point pt2)
{
	t_bres *bres;

	if (!(bres = malloc(sizeof(t_bres))))
		ft_error();
	bres->dx = pt2.x - pt1.x;
	bres->dy = pt2.y - pt1.y;
	bres->dx = bres->dx < 0 ? -bres->dx : bres->dx;
	bres->dy = bres->dy < 0 ? -bres->dy : bres->dy;
	bres->sx = pt2.x < pt1.x ? -1 : 1;
	bres->sy = pt2.y < pt1.y ? -1 : 1;
	if (bres->dx > bres->dy)
	{
		bres->e = 2 * bres->dy - bres->dx;
		bres->inc1 = 2 * (bres->dy - bres->dx);
		bres->inc2 = 2 * (bres->dy);
	}
	else
	{
		bres->e = 2 * bres->dx - bres->dy;
		bres->inc1 = 2 * (bres->dx - bres->dy);
		bres->inc2 = 2 * (bres->dx);
	}
	return (bres);
}

void		draw_line(t_point pt1, t_point pt2, t_map *map)
{
	t_bres	*bres;

	bres = get_bres(pt1, pt2);
	if (bres->dx > bres->dy)
		bresenmann_1(bres, pt1, map);
	else
		bresenmann_2(bres, pt1, map);
}
