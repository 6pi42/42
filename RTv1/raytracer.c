/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 16:47:16 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/27 17:08:13 by cboyer           ###   ########.fr       */
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

void	init_inter(t_sphere *s, int i, int j, t_map *map)
{
	double		a;
	double		b;
	double		c;
	double		t;
	double		d;
	double		tmp;
	t_vec		ray;
	t_cam		cam;

	t = -1;
	cam = map->tab->cam;
	ray = init_ray(map, j, i);
	a = ray.x * ray.x + ray.y * ray.y + ray.z * ray.z;
	b =  2 * (ray.x * (cam.pos.x - s->pos.x)
			+ ray.y * (cam.pos.y - s->pos.y)
			+ ray.z * (cam.pos.z - s->pos.z));
	c = (cam.pos.x - s->pos.x) * (cam.pos.x - s->pos.x)
	  + (cam.pos.y - s->pos.y) * (cam.pos.y - s->pos.y)
	  + (cam.pos.z - s->pos.z) * (cam.pos.z - s->pos.z)
		- s->radius * s->radius;
	d = (b * b) - (4 * a * c);
	if (d == 0)
		t = (-b + sqrt(d)) / (2 * a);
	else if (d > 0)
	{
		t = (-b - sqrt(d)) / (2 * a);
		tmp = (-b + sqrt(d)) / (2 * a);
		if (t > tmp && tmp > 0)
			t = tmp;
	}
	s->t = t <= 0 ? -1 : t;
}

int		get_smaller(t_sphere *sphere, int c)
{
	int		i;
	int		j;
	double	tmp;

	if (c >= 1)
		tmp = sphere[0].t;
	else
		return (-1);
	j = 0;
	i = 0;
	while (i < c)
	{
		if (tmp < 0 || (tmp > sphere[i].t && sphere[i].t > 0))
		{
			tmp = sphere[i].t;
			j = i;
		}
		i++;
	}
	j = tmp == -1 ? -1 : j;
	return (j);
}

void *nearest(int y, int x, t_map *map, t_sphere *sphere, int c)
{
	int		i;
	int		small;

	i = 0;
	while (i < c)
	{
		init_inter(&map->tab->sphere[i], y, x, map);
		i++;
	}
	small = get_smaller(map->tab->sphere, c);
	if (small != -1)
		return ((void*)(&sphere[small]));
	else
		return (NULL);
}

void	raytracer(t_map *map)
{
	int		i;
	int		j;
	void	*stru[1];

	i = 0;
	while (i < map->tab->screen.y)
	{
		j = 0;
		while (j < map->tab->screen.x)
		{
			stru[0] = nearest(i, j, map, map->tab->sphere, map->tab->nb_sphere);
			if (stru[0] != NULL && *(double*)stru[0] != -1)
			{
				printf("%d\n", *(int*)(stru[0] + sizeof(double)));
				pixel_put(map, i, j, *(int*)(stru[0] + sizeof(double)));
			}
			j++;
		}
		i++;
	}
}
