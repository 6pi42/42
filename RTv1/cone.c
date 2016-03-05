/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 13:50:14 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/05 14:29:23 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	get_inter_cone(t_cone *cone, t_vec ray, t_vec org)
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	t;
	double	tmp;

	t = -1;
	a = ray.x * ray.x + ray.y * ray.y + ray.z * ray.z;
	b = 2 * ((org.x - cone->pos.x) * ray.z + (org.z - cone->pos.z) * ray.z -
		(org.y - cone->pos.y) * ray.y);
	c = (org.x - cone->pos.x) * (org.x - cone->pos.x) +
		(org.z - cone->pos.z) * (org.z - cone->pos.z) -
		(org.y - cone->pos.y) * (org.y - cone->pos.y);
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
	cone->t = t > 0 ? t : -1;
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
