/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 16:47:16 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/16 15:24:02 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec	intersection(void *obj, t_vec ray, t_vec org)
{
	t_vec	inter;
	double	t;

	t = *(double*)(obj);
	inter.x = org.x + ray.x * t;
	inter.y = org.y + ray.y * t;
	inter.z = org.z + ray.z * t;
	return (inter);
}

t_vec	init_ray(t_map *map, int x, int y)
{
	t_vec	ray;

	ray.x = (double)x - ((double)map->tab->screen.x / 2);
	ray.y = (double)y - ((double)map->tab->screen.y / 2);
	ray.z = -(map->tab->screen.x / (2 * tan((FOV / 2) * M_PI / 180.0)));
	normalize_vec(&ray);
	return (ray);
}

void	*smaller_void(void **st)
{
	int		i;
	double	tmp;
	int		j;

	i = 0;
	tmp = -1;
	j = -1;
	while (i < NB_OBJ)
	{
		if (st[i] != NULL && ((tmp == -1 && (*(double*)st[i] != -1))
			|| (tmp > (*(double*)st[i]))))
		{
			tmp = *(double*)st[i];
			j = i;
		}
		i++;
	}
	if (j == -1)
		return (NULL);
	return (st[j]);
}

void	nearest_obj(t_map *map, t_vec ray, t_vec org, void **st)
{
	st[0] = nearest_sphere(ray , map, map->tab->sphere, org);
	st[1] = nearest_plan(org, ray, map);
	st[2] = nearest_cyl(ray, map, map->tab->cylinder, org);
	st[3] = nearest_cone(ray, map, map->tab->cone, org);
}

void	raytracer(t_map *map)
{
	int		y;
	int		x;
	void	*st[NB_OBJ];
	int		rgb;
	void	*small;
	t_vec	ray;

	y = 0;
	while (y < map->tab->screen.y)
	{
		x = 0;
		while (x < map->tab->screen.x)
		{
			ray = init_ray(map, x, y);
			nearest_obj(map, ray, map->tab->cam.pos, st);
			if ((small = smaller_void(st)) != NULL)
			{
				rgb = *(int*)(small + sizeof(double));
				if (map->tab->nb_spot)
					rgb = multi_spot(st, small, ray, map);
				pixel_put(map, x, y, rgb);
			}
			x++;
		}
		y++;
	}
}
