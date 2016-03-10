/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 19:42:15 by Client            #+#    #+#             */
/*   Updated: 2016/03/10 12:58:11 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	get_inter_sphere(t_sphere *s, t_vec ray, t_vec org)
{
	double		a[5];
	double		tmp;

	a[3] = -1;
	a[0] = ray.x * ray.x + ray.y * ray.y + ray.z * ray.z;
	a[1] = 2 * (ray.x * (org.x - s->pos.x) + ray.y * (org.y - s->pos.y)
	+ ray.z * (org.z - s->pos.z));
	a[2] = (org.x - s->pos.x) * (org.x - s->pos.x) + (org.y - s->pos.y) *
	(org.y - s->pos.y) + (org.z - s->pos.z) * (org.z - s->pos.z) -
	s->radius * s->radius;
	a[4] = (a[1] * a[1]) - (4 * a[0] * a[2]);
	if (a[4] == 0 && a[0] != 0)
		a[3] = (-a[1] + sqrt(a[4])) / (2 * a[0]);
	else if (a[4] > 0 && a[0] != 0)
	{
		a[3] = (-a[1] - sqrt(a[4])) / (2 * a[0]);
		tmp = (-a[1] + sqrt(a[4])) / (2 * a[0]);
		if (a[3] > tmp && tmp > 0)
			a[3] = tmp;
	}
	printf("t %f\n", a[3]);
	s->t = a[3] <= 0 ? -1 : a[3];
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

void	*nearest_sphere(t_vec ray, t_map *map, t_sphere *sphere, t_vec org)
{
	int		i;
	int		small;
	int		c;

	c = map->tab->nb_sphere;
	i = 0;
	while (i < c)
	{
		get_inter_sphere(&map->tab->sphere[i], ray, org);
		i++;
	}
	small = get_smaller_sphere(map->tab->sphere, c);
	if (small != -1)
		return ((void*)(&sphere[small]));
	else
		return (NULL);
}
