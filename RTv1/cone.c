/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 13:50:14 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/16 14:38:32 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
/*
t_vec	get_normal_cone(t_cone *c, t_vec ray, t_vec org, double a)
{
	t_vec	norm;
	double	m;

	m = a / (c->radius * c->radius);
	norm.x = (ray.x * c->t) + (org.x - c->pos.x) -
		(1 + c->radius * c->radius) * (c->rot.x) * m;
	norm.y = (ray.y * c->t) + (org.y - c->pos.y) -
		(1 + c->radius * c->radius) * (c->rot.y) * m;
	norm.x = (ray.z * c->t) + (org.z - c->pos.z) -
		(1 + c->radius * c->radius) * (c->rot.z) * m;
	normalize_vec(&norm);
	return (norm);
}
*/
t_vec   get_normal_cone(t_cone *cyl, t_vec ray, t_vec org)
{
	t_vec	norm;
	double	m;

	m = (dot_vec(ray, cyl->rot) * cyl->t) +
		(dot_vec(sous_vec_n(cyl->pos, org), cyl->rot));
	norm.x = (ray.x * cyl->t) + (org.x - cyl->pos.x) - (cyl->rot.x * m);
	norm.y = (ray.y * cyl->t) + (org.y - cyl->pos.y) - (cyl->rot.y * m);
	norm.z = (ray.z * cyl->t) + (org.z - cyl->pos.z) - (cyl->rot.z * m);
	normalize_vec(&norm);
	return (norm);
}

void	get_inter_cone(t_cone *cone, t_vec ray, t_vec org)
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	t1;
	double	t2;
	double	k;

	k = cone->radius;
	t1 = -1;
	a = dot_vec(ray, ray) - (1 + k * k) *
		(dot_vec(ray, cone->rot) * dot_vec(ray, cone->rot));
	b = 2 * (dot_vec(ray, sous_vec_n(cone->pos, org)) - (1 + k * k) *
		(dot_vec(ray, cone->rot) * dot_vec(sous_vec_n(cone->pos, org), cone->rot)));
	c = dot_vec(sous_vec_n(cone->pos, org), sous_vec_n(cone->pos, org)) -
		(1 + k * k) * (dot_vec(sous_vec_n(cone->pos, org), cone->rot) *
		dot_vec(sous_vec_n(cone->pos, org), cone->rot));
	d = (b * b) - (4 * a * c);
	if (d >= 0)
	{
		t1 = (-b + sqrt(d)) / (2 * a);
		t2 = (-b - sqrt(d)) / (2 * a);
		if (t1 > t2 && t2 > 0)
			t1 = t2;
	}
	cone->t = t1 > 0 ? t1 : -1;
	if (t1 > 0)
		cone->norm = get_normal_cone(cone, ray, org);
}

int		get_smaller_cone(t_cone *cone, int c)
{
	int		i;
	int		j;
	double	tmp;

	if (c >= 1)
		tmp = cone[0].t;
	else
		return (-1);
	j = 0;
	i = 0;
	while (i < c)
	{
		if (tmp <= 0 || (tmp > cone[i].t && cone[i].t > 0))
		{
			tmp = cone[i].t;
			j = i;
		}
		i++;
	}
	j = tmp == -1 ? -1 : j;
	return (j);
}

void	*nearest_cone(t_vec ray, t_map *map, t_cone *cone, t_vec org)
{
	int	i;
	int	small;
	int	c;

	c = map->tab->nb_cone;
	i = 0;
	while (i < c)
	{
		get_inter_cone(&map->tab->cone[i], ray, org);
		i++;
	}
	small = get_smaller_cone(map->tab->cone, c);
	if (small != -1)
		return ((void*)(&cone[small]));
	else
		return (NULL);
}
