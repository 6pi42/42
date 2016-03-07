/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 11:27:19 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/07 12:32:49 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	get_inter_cyl(t_cone *cyl, t_vec ray, t_vec org, t_map *map)
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	t1;
	double	t2;
	double	tmp;
	double	y1;
	double	y2;
	double	min;
	double	max;

	t1 = -1;
	a = ray.x * ray.x + ray.z * ray.z;
	b = 2 * (ray.x * (org.x - cyl->pos.x) + ray.z * (org.z - cyl->pos.z));
	c = (((org.x - cyl->pos.x) * (org.x - cyl->pos.x)) +
		((org.z - cyl->pos.z) * (org.z - cyl->pos.z))) -
		cyl->radius * cyl->radius;
	d = (b * b) - (4 * a * c);
	if (d == 0)
	{
		t1 = (-b + sqrt(d)) / (2 * a);
		t2 = t1;
	}
	else if (d > 0)
	{
		t1 = (-b + sqrt(d)) / (2 * a);
		t2 = (-b - sqrt(d)) / (2 * a);
		if (t1 > t2 && t2 > 0)
		{
			tmp = t1;
			t1 = t2;
			t2 = tmp;
		}
	}
	max = init_ray(map, cyl->pos.x, cyl->pos.y + cyl->height / 2).y;
	min = init_ray(map, cyl->pos.x, cyl->pos.y - cyl->height / 2).y;
	if (t1 != -1)
	{
		y1 = (org.y - cyl->pos.y) + t1 * ray.y;
		y2 = (org.y - cyl->pos.y) + t2 * ray.y;
/*		if ((y1 < min || y1 > max))
			t1 = -1;
		printf("min | %f | max | %f | y1 | %f | y2 | %f |\n", min, max, y1, y2);
*/	}
	cyl->t = t1 <= 0 ? -1 : t1;
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

	c = map->tab->nb_cylinder;
	i = 0;
	while (i < c)
	{
		get_inter_cyl(&map->tab->cylinder[i], ray, org, map);
		i++;
	}
	small = get_smaller_cyl(map->tab->cylinder, c);
	if (small != -1)
		return ((void*)(&cyl[small]));
	else
		return (NULL);
}
