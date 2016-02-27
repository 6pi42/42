/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Client <Client@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 19:42:15 by Client            #+#    #+#             */
/*   Updated: 2016/02/27 19:58:28 by Client           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	get_inter_sphere(t_sphere *s, int i, int j, t_map *map)
{
	double		a;
	double		b;
	double		c;
	double		t;
	double		d;
	double		tmp;
	t_vec		ray;

	t = -1;
	ray = init_ray(map, j, i);
	a = ray.x * ray.x + ray.y * ray.y + ray.z * ray.z;
	b =  2 * (ray.x * (map->tab->cam.pos.x - s->pos.x)
			+ ray.y * (map->tab->cam.pos.y - s->pos.y)
			+ ray.z * (map->tab->cam.pos.z - s->pos.z));
	c = (map->tab->cam.pos.x - s->pos.x) * (map->tab->cam.pos.x - s->pos.x)
	  + (map->tab->cam.pos.y - s->pos.y) * (map->tab->cam.pos.y - s->pos.y)
	  + (map->tab->cam.pos.z - s->pos.z) * (map->tab->cam.pos.z - s->pos.z)
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

int		get_smaller_sphere(t_sphere *sphere, int c)
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

void *nearest_sphere(int y, int x, t_map *map, t_sphere *sphere)
{
	int		i;
	int		small;
	int		c;

	c = map->tab->nb_sphere;
	i = 0;
	while (i < c)
	{
		get_inter_sphere(&map->tab->sphere[i], y, x, map);
		i++;
	}
	small = get_smaller_sphere(map->tab->sphere, c);
	if (small != -1)
		return ((void*)(&sphere[small]));
	else
		return (NULL);
}
