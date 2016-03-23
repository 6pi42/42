/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 11:27:19 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/23 16:14:14 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec	get_normal_cyl(t_cone *cyl, t_vec ray, t_vec org)
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

void	get_inter_cyl(t_cone *cyl, t_vec ray, t_vec org, int n)
{
	double	a[4];
	double	t1;
	double	t2;

	t1 = -1;
	a[0] = dot_vec(ray, ray) - (dot_vec(ray, cyl->rot) *
		dot_vec(ray, cyl->rot));
	a[1] = 2 * (dot_vec(ray, sous_vec_n(cyl->pos, org)) -
	(dot_vec(ray, cyl->rot) * dot_vec(sous_vec_n(cyl->pos, org), cyl->rot)));
	a[2] = dot_vec(sous_vec_n(cyl->pos, org), sous_vec_n(cyl->pos, org)) -
		(dot_vec(sous_vec_n(cyl->pos, org), cyl->rot) *
		dot_vec(sous_vec_n(cyl->pos, org), cyl->rot)) -
		cyl->radius * cyl->radius;
	a[3] = (a[1] * a[1]) - (4 * a[0] * a[2]);
	if (a[3] >= 0)
	{
		t1 = (-a[1] + sqrt(a[3])) / (2 * a[0]);
		t2 = (-a[1] - sqrt(a[3])) / (2 * a[0]);
		if (t1 > t2 && t2 > 0)
			t1 = t2;
	}
	cyl->t = t1 <= 0 ? -1 : t1;
	if (t1 > 0 && n)
		cyl->norm = get_normal_cyl(cyl, ray, org);
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

void	*nearest_cyl(t_vec ray, t_map *map, int n, t_vec org)
{
	int	i;
	int	small;
	int	c;
	t_cone	*cyl;

	cyl = map->tab->cylinder;
	c = map->tab->nb_cylinder;
	i = 0;
	while (i < c)
	{
		get_inter_cyl(&map->tab->cylinder[i], ray, org, n);
		i++;
	}
	small = get_smaller_cyl(map->tab->cylinder, c);
	if (small != -1)
		return ((void*)(&cyl[small]));
	else
		return (NULL);
}
