/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 19:42:15 by Client            #+#    #+#             */
/*   Updated: 2016/03/23 16:10:55 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	get_inter_sphere(t_sphere *s, t_vec ray, t_vec opos)
{
	double a;
	double b;
	double c;
	double d;
	double t;

	a = ray.x * ray.x + ray.y * ray.y + ray.z * ray.z;
	b = 2.0 * (ray.x * (opos.x - s->pos.x)
		+ ray.y * (opos.y - s->pos.y)
		+ ray.z * (opos.z - s->pos.z));
	c = (opos.x - s->pos.x) * (opos.x - s->pos.x)
		+ (opos.y - s->pos.y) * (opos.y - s->pos.y)
		+ (opos.z - s->pos.z) * (opos.z - s->pos.z)
		- s->radius * s->radius;
	d = (b * b) - (4 * a * c);
	if (d >= 0.0)
	{
		t = (-b + sqrt(d)) / (2 * a);
		if ((-b - sqrt(d)) / (2 * a) < t)
			t = (-b - sqrt(d)) / (2 * a);
		s->t = t > 0 ? t : -1;
	}
	else
		s->t = -1;
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
		if (tmp <= 0 || (tmp > sphere[i].t && sphere[i].t > 0))
		{
			tmp = sphere[i].t;
			j = i;
		}
		i++;
	}
	j = tmp == -1 ? -1 : j;
	return (j);
}

void	*nearest_sphere(t_vec ray, t_map *map, int n, t_vec org)
{
	int			i;
	int			small;
	int			c;
	t_sphere	*sphere;

	sphere = map->tab->sphere;
	c = map->tab->nb_sphere;
	i = 0;
	while (i < c)
	{
		get_inter_sphere(&map->tab->sphere[i], ray, org);
		i++;
	}
	small = get_smaller_sphere(map->tab->sphere, c);
	if (small != -1)
	{
		if (n)
			sphere[small].norm = get_normal_sphere(&sphere[small], ray, map);
		return ((void*)(&sphere[small]));
	}
	else
		return (NULL);
}
