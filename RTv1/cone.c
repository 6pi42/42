/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 13:50:14 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/23 16:15:20 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec	get_normal_cone(t_cone *cyl, t_vec ray, t_vec org)
{
	t_vec	norm;
	double	m;
	double	k;

	k = cyl->radius;
	m = (dot_vec(ray, cyl->rot) * cyl->t) +
		(dot_vec(sous_vec_n(cyl->pos, org), cyl->rot));
	norm.x = (ray.x * cyl->t) + (org.x - cyl->pos.x) -
	((1 + k * k) * cyl->rot.x * m);
	norm.y = (ray.y * cyl->t) + (org.y - cyl->pos.y) -
	((1 + k * k) * cyl->rot.y * m);
	norm.z = (ray.z * cyl->t) + (org.z - cyl->pos.z) -
	((1 + k * k) * cyl->rot.z * m);
	normalize_vec(&norm);
	return (norm);
}

void	get_inter_cone(t_cone *cone, t_vec ray, t_vec org, int n)
{
	double	a[6];
	double	k;

	k = cone->radius;
	a[0] = -1;
	a[0] = dot_vec(ray, ray) - (1 + k * k) *
		(dot_vec(ray, cone->rot) * dot_vec(ray, cone->rot));
	a[1] = 2 * (dot_vec(ray, sous_vec_n(cone->pos, org)) -
		(1 + k * k) * (dot_vec(ray, cone->rot) *
		dot_vec(sous_vec_n(cone->pos, org), cone->rot)));
	a[2] = dot_vec(sous_vec_n(cone->pos, org), sous_vec_n(cone->pos, org)) -
		(1 + k * k) * (dot_vec(sous_vec_n(cone->pos, org), cone->rot) *
		dot_vec(sous_vec_n(cone->pos, org), cone->rot));
	a[3] = (a[1] * a[1]) - (4 * a[0] * a[2]);
	if (a[3] >= 0)
	{
		a[4] = (-a[1] + sqrt(a[3])) / (2 * a[0]);
		a[5] = (-a[1] - sqrt(a[3])) / (2 * a[0]);
		if (a[4] > a[5] && a[5] > 0)
			a[4] = a[5];
	}
	cone->t = a[4] > 0 ? a[4] : -1;
	if (a[4] > 0 && n)
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

void	*nearest_cone(t_vec ray, t_map *map, int n, t_vec org)
{
	int		i;
	int		small;
	int		c;
	t_cone	*cone;

	cone = map->tab->cone;
	c = map->tab->nb_cone;
	i = 0;
	while (i < c)
	{
		get_inter_cone(&map->tab->cone[i], ray, org, n);
		i++;
	}
	small = get_smaller_cone(map->tab->cone, c);
	if (small != -1)
		return ((void*)(&cone[small]));
	else
		return (NULL);
}
