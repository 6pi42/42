/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 16:47:16 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/24 11:48:52 by cboyer           ###   ########.fr       */
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
	ray.y = ((double)map->tab->screen.y / 2) - (double)y;
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

void	nearest_obj_n(t_map *map, t_vec ray, t_vec org, void **st)
{
	st[0] = nearest_sphere(ray, map, 1, org);
	st[1] = nearest_plan(org, ray, map);
	st[2] = nearest_cyl(ray, map, 1, org);
	st[3] = nearest_cone(ray, map, 1, org);
}

void	nearest_obj(t_map *map, t_vec ray, t_vec org, void **st)
{
	st[0] = nearest_sphere(ray, map, 0, org);
	st[1] = nearest_plan(org, ray, map);
	st[2] = nearest_cyl(ray, map, 0, org);
	st[3] = nearest_cone(ray, map, 0, org);
}

void	raytracer(t_map *map)
{
	int		x[2];
	void	*st[NB_OBJ];
	int		rgb;
	void	*small;
	t_vec	ray[3];

	x[0] = 0;
	while (x[0] < map->tab->screen.y)
	{
		x[1] = 0;
		while (x[1] < map->tab->screen.x)
		{
			rgb = 0x000000;
			ray[0] = init_ray(map, x[1], x[0]);
			nearest_obj_n(map, ray[0], map->tab->cam.pos, st);
			if ((small = smaller_void(st)) != NULL)
				rgb = multi_spot(st, small, ray, map);
			pixel_put(map, x[1], x[0], rgb);
			x[1]++;
		}
		x[0]++;
	}
}
