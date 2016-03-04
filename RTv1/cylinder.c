/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 11:27:19 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/04 15:27:28 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	get_inter_cyl(t_cone *cyl, t_vec ray, t_vec org)
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	t;
	double	tmp;
	double	p;

	t = -1;
	p = (org.y - cyl->pos.y);
	a = ray.x * ray.x + ray.z * ray.z;
	b = 2 * (ray.x * (org.x - cyl->pos.x) + ray.z * (org.z - cyl->pos.z));
	c = (((org.x - cyl->pos.x) * (org.x - cyl->pos.x)) +
		((org.z - cyl->pos.z) * (org.z - cyl->pos.z))) -
		cyl->radius * cyl->radius;
	d = (b * b) - (4 * a * c);
	if (d == 0)
		t = (-b + sqrt(d)) / (2 * a);
	else if (d > 0)
	{
		t = (-b + sqrt(d)) / (2 * a);
		tmp = (-b - sqrt(d)) / (2 * a);
		if (t > tmp && tmp > 0)
			t = tmp;
	}
	if (t != -1)
	{
		p = ray.y * t + p;
		if (p < cyl->pos.y || p > cyl->pos.y + cyl->height)
			t = -1;
	}
	cyl->t = t <= 0 ? -1 : t;
}

int		get_smaller_cyl(t_cone *cyl, int c)
{
	int		i;
	int		j;
	double	tmp;

	if (c >= 1)
		tmp = cyl[0].t;
	else
		return (-1);
	j = 0;
	i = 0;
	while (i < c)
	{
		if (tmp <= 0 || (tmp > cyl[i].t && cyl[i].t > 0))
		{
			tmp = cyl[i].t;
			j = i;
		}
		i++;
	}
	j = tmp == -1 ? -1 : j;
	return (j);
}

void	*nearest_cyl(t_vec ray, t_map *map, t_cone *cyl, t_vec org)
{
	int	i;
	int	small;
	int	c;

	c = map->tab->nb_sphere;
	i = 0;
	while (i < c)
	{
		get_inter_cyl(&map->tab->cylinder[i], ray, org);
		i++;
	}
	small = get_smaller_cyl(map->tab->cylinder, c);
	if (small != -1)
		return ((void*)(&cyl[small]));
	else
		return (NULL);
}
