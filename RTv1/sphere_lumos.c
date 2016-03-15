/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_lumos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 13:31:54 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/15 13:42:57 by cboyer           ###   ########.fr       */
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



int		sphere_lumos_diff(t_map *map, t_sphere *sphere, t_vec ray, t_vec org)
{
	int		rgb;
	t_vec	light;
	double	angle;
	t_vec	norm;

	light = get_light_ray((void*)sphere, ray, map, org);
	norm = get_normal_sphere(sphere, ray, map);
	angle = acos(dot_vec(light, norm));
	if (angle <= 0)
		rgb = 0x000000;
	else
		rgb = light_rgb(sphere->rgb, angle * 0.6);
	return (rgb);
}

int		sphere_lumos_spec(t_map *map, t_sphere *sphere, t_vec ray, t_vec org)
{
	t_vec	norm;
	t_vec	light;
	t_vec	half;
	double	tmp;
	double	intensity;

	light = get_light_ray((void*)sphere, ray, map, org);
	norm = get_normal_sphere(sphere, ray, map);
	if ((dot_vec(norm, light)) > 0.0)
	{
		half = add_vec(ray, light);
		tmp = fmax(dot_vec(norm, half), 0.0);
		intensity = pow(tmp, 0.5);
		return (light_rgb(sphere->rgb, intensity));
	}
	return (sphere->rgb);
}

int	sphere_lumos(t_map *map, t_sphere *sphere, t_vec ray, t_vec org)
{
	int	diffuse;
	int	spec;

	diffuse = sphere_lumos_diff(map, sphere, ray, org);
	spec = sphere_lumos_spec(map, sphere, ray, org);
	return (diffuse);
}
