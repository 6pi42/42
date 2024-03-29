/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 16:47:16 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/30 17:40:44 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec	init_ray(t_map *map, double x, double y)
{
	t_vec	ray;
	t_vec	tmp;
	t_vec	rot;

	rot = map->tab->cam.rotate;
	ray.x = (x - (map->tab->screen.x / 2));
	ray.y = ((map->tab->screen.y - y) - (map->tab->screen.y / 2));
	ray.z = -(map->tab->screen.x / (2 * tan((50 / 2) * M_PI / 180.0)));
	normalize_vec(&ray);
	tmp = ray;
	ray.x = tmp.x * cos(to_rad(rot.z)) - tmp.y * sin(to_rad(rot.z));
	ray.y = tmp.x * sin(to_rad(rot.z)) + tmp.y * cos(to_rad(rot.z));
	tmp = ray;
	ray.y = tmp.y * cos(to_rad(rot.x)) - tmp.z * sin(to_rad(rot.x));
	ray.z = tmp.y * sin(to_rad(rot.x)) + tmp.z * cos(to_rad(rot.x));
	tmp = ray;
	ray.z = tmp.z * cos(to_rad(rot.y)) - tmp.x * sin(to_rad(rot.y));
	ray.x = tmp.z * sin(to_rad(rot.y)) + tmp.x * cos(to_rad(rot.y));
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
			|| (tmp > (*(double*)st[i]) && *(double*)st[i] != -1)))
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
	st[0] = nearest_sphere(ray, map, 0, org);
	st[1] = nearest_plan(org, ray, map);
	st[2] = nearest_cyl(ray, map, 0, org);
	st[3] = nearest_cone(ray, map, 0, org);
}

void	raytracer(t_map *map)
{
	int		x;
	int		y;

	y = 0;
	while (y < map->tab->screen.y)
	{
		x = 0;
		while (x < map->tab->screen.x)
		{
			multi_sampling(x, y, map);
			x++;
		}
		y++;
	}
}
