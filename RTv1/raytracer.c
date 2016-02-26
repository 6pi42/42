/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 16:47:16 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/26 06:57:29 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec    init_ray(t_map *map, int x, int y)
{
	t_vec   ray;
	ray.x = (x - map->tab->screen.x / 2) * 1;
	ray.y = (y - map->tab->screen.y / 2) * 1;
	ray.z = -(map->tab->screen.x / (2 * tan((90 / 2) * M_PI / 180.0)));
	return (ray);
}

void	init_inter(t_sphere s, int i, int j, t_map *map)
{
	double		a;
	double		b;
	double		c;
	double		t;
	double		d;
	double		tmp;
	t_vec		ray;

	ray = init_ray(map, j, i);
	a = ray.x * ray.x + ray.y * ray.y + ray.z * ray.z;
	b = 2 * ray.x * (map->tab->cam.pos.x - s.pos.x) + 2 * ray.y *
		(map->tab->cam.pos.y - s.pos.y) + 2 * ray.z *
			(map->tab->cam.pos.z - s.pos.z);

	c = (s.pos.x * s.pos.x + s.pos.y * s.pos.y + s.pos.z * s.pos.z)
	 	+ (ray.x * ray.x + ray.y * ray.y + ray.z * ray.z)
		- 2 * (ray.x * s.pos.x + ray.y * s.pos.y + ray.z * s.pos.z)
		- s.radius * s.radius;
	d = b * b + 4 * a * c;
//	printf("%f\n", d);
	if (d == 0)
		t = (-b - sqrt(d)) / (2 * a);
	else if (d > 0)
	{
		t = (-b - sqrt(d)) / (2 * a);
		tmp = (-b + sqrt(d)) / (2 * a);
		t = t > tmp ? t : tmp;
	}
	else
		return ;
	pixel_put(map, j, i, 0x00FF00);
}

void	raytracer(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	while (i < map->tab->screen.y)
	{
		j = 0;
		while (j < map->tab->screen.x)
		{
			init_inter(map->tab->sphere[0], i, j, map);
//check_nearest(map->tab, i, j);
			j++;
		}
		i++;
	}
	printf("end\n");
}
