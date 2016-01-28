/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 16:38:14 by cboyer            #+#    #+#             */
/*   Updated: 2016/01/28 15:53:01 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	get_vertical(t_map *map, double a, int xa)
{
	int	ya;
	t_point	p1;
	int		i;

	i = 0;
	if (xa >= 0)
		p1.x = map->cam.x / UNIT * (UNIT) + UNIT;
	else
		p1.x = map->cam.x / UNIT * (UNIT) - 1;
	ya = UNIT * tan(a * M_PI / 180);
	p1.y = map->cam.y + (map->cam.x - p1.x) * tan(a * M_PI / 180);
	while (42)
	{
		if (map->map[p1.y / UNIT][p1.x / UNIT].z > 0)
			break ;
		p1.x += xa;
		p1.y += ya;
	}
	return (fabs(map->cam.x - p1.x) / cos(a * M_PI / 180));
}

static int	get_horizontal(t_map *map, double a, int ya)
{
	int	xa;
	t_point	p1;
	int		i;

	i = 0;
	if (ya >= 0)
		p1.y = map->cam.y / UNIT * (UNIT) - 1;
	else
		p1.y = map->cam.y / UNIT * (UNIT) + UNIT;
	p1.x = map->cam.x + (map->cam.y - p1.y) / tan(a * M_PI / 180);
	xa = ya / tan(a * M_PI / 180);
	while (42)
	{
		if (map->map[p1.y / UNIT][p1.x / UNIT].z > 0)
			break ;
		p1.x += xa;
		p1.y += ya;
	}
	return (fabs(map->cam.x - p1.x) / cos(a * M_PI / 180));
}

static double	get_dist(t_map *map, double a)
{
	double	d1;
	double	d2;

	d1 = get_horizontal(map, a, a <= 180 ? UNIT : -UNIT);
	d2 = get_vertical(map, a, a < 90 || a > 270 ? -UNIT : UNIT);
	return (d2 > d1 ? d1 : d2);
}

void	raycasting(t_map *map)
{
	int		i;
	double	angle;
	double	height;
	double	dist;
	double beta;
	t_point	p[2];

	i = 0;
	angle = map->cam.r - map->cam.fov / 2;
	beta = -(map->cam.fov / 2);
	while (i < WIDTH)
	{
		dist = get_dist(map, angle) * cos(beta * M_PI * 180);
		height = UNIT / dist * (WIDTH / 2 / tan(map->cam.fov / 2 * M_PI / 180));
		p[0].y = HEIGHT / 2 - (height / 2);
		p[0].x = i;
		p[1].y = p[0].y + height;
		p[1].x = p[0].x;
		draw_line(p[0], p[1], map);
		angle = fmod(angle + map->cam.fov / WIDTH, 360.0);
		beta += map->cam.fov / WIDTH;
		i++;
	}
}
