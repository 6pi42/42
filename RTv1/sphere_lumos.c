/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_lumos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 13:31:54 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/07 16:15:05 by cboyer           ###   ########.fr       */
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



int		sphere_lumos_diff(t_map *map, t_sphere *sphere, t_vec ray)
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
		rgb = light_rgb(sphere->rgb, angle * 0.6);
	return (rgb);
}

int		sphere_lumos_spec(t_map *map, t_sphere *sphere, t_vec ray)
{
	t_vec	norm;
	double	refl;
	t_vec	phong;
	double	coef;
	int		rgb;
	t_vec	light;

	rgb = 0x000000;
	light = get_light_ray((void*)sphere, ray, map);
	norm = get_normal_sphere(sphere, norm, map);
	refl = 2.0 * dot_vec(norm, light);
	phong = sous_vec(light, mult_int_vec(norm, refl));
	coef = dot_vec(phong, ray) > 0.0 ? dot_vec(phong, ray) : 0.0;
	if (coef > 0)
		rgb = light_rgb(sphere->rgb, acos(coef));
	return (rgb);

}

int	sphere_lumos(t_map *map, t_sphere *sphere, t_vec ray)
{
	int	rgb;
	int	rgb2;

	rgb = sphere_lumos_diff(map, sphere, ray);
	rgb2 = sphere_lumos_spec(map, sphere, ray);
	return (rgb);
}