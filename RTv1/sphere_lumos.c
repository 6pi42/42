/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_lumos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 13:31:54 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/03 16:10:44 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec	get_normal_sphere(t_sphere *sphere, t_vec ray, t_map *map)
{
	t_vec norm;

	norm.x = (map->tab->cam.pos.x + ray.x * sphere->t) - sphere->pos.x;
	norm.y = (map->tab->cam.pos.y + ray.y * sphere->t) - sphere->pos.y;
	norm.z = (map->tab->cam.pos.z + ray.z * sphere->t) - sphere->pos.z;
	normalize_vec(&norm);
	return (norm);
}

t_vec	get_light_ray(void *obj, t_vec ray, t_map *map)
{
	t_vec	light;
	double	t;

	t = *(double*)obj;
	light.x = (map->tab->cam.pos.x + ray.x * t) - map->tab->spot.x;
	light.y = (map->tab->cam.pos.y + ray.y * t) - map->tab->spot.y;
	light.z = (map->tab->cam.pos.z + ray.z * t) - map->tab->spot.z;
	normalize_vec(&light);
	return (light);
}

int sphere_lumos(t_map *map, t_sphere *sphere, t_vec ray)
{
	int		rgb;
	t_vec	light;
	double	angle;
	t_vec	norm;

	light = get_light_ray((void*)sphere, ray, map);
	norm = get_normal_sphere(sphere, ray, map);
	angle = acos(dot_vec(light, norm));
	if (angle <= 0)
		rgb = 0x000000;
	else
		rgb = light_rgb(sphere->rgb, angle);
	return (rgb);
}
