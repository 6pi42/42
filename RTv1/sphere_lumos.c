/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_lumos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 13:31:54 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/17 17:09:02 by cboyer           ###   ########.fr       */
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

int		sphere_lumos_diff(t_map *map, t_sphere *sphere, t_vec ray, int rgb)
{
	t_vec	light;
	double	angle;
	t_vec	norm;
	t_vec	inter;

	inter = intersection(sphere, ray, map->tab->cam.pos);
	light = sous_vec(*map->tab->spot_a, inter);
	norm = get_normal_sphere(sphere, ray, map);
	angle = acos(dot_vec(light, norm));
	if (angle <= 0)
		rgb = 0x000000;
	else
		rgb = light_rgb(rgb, angle * 0.6);
	return (rgb);
}

int		sphere_lumos_spec(t_map *map, t_sphere *sphere, t_vec ray, int rgb)
{
	t_vec	norm;
	t_vec	light;
	t_vec	half;
	double	tmp;
	t_vec	inter;

	inter = intersection(sphere, ray, map->tab->cam.pos);
	light = sous_vec(*map->tab->spot_a, inter);
	norm = get_normal_sphere(sphere, ray, map);
	half = add_vec(norm, light);
	tmp = fmax(dot_vec(norm, half), 0.0);
	tmp = pow(tmp, 2.0);
	return (reflection(rgb, tmp));
}

int		sphere_lumos(t_map *map, t_sphere *sphere, t_vec ray, int rgb)
{
	rgb = sphere_lumos_diff(map, sphere, ray, rgb);
	rgb = sphere_lumos_spec(map, sphere, ray, rgb);
	return (rgb);
}
