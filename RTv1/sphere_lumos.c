/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_lumos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 13:31:54 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/16 11:48:39 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int        reflection(int rgb, double dot)
{
	unsigned int    red;
	unsigned int    green;
	unsigned int    blue;

	red = (rgb & 0xFF0000) >> 16;
	green = (rgb & 0xFF00) >> 8;
	blue = rgb & 0xFF;
	dot = 1.0 - dot;
	red *= dot;
	blue *= dot;
	green *= dot;
	red = red > 255 ? 255 : red;
	blue = blue > 255 ? 255 : blue;
	green = green > 255 ? 255 : green;
	rgb = red << 16 | green << 8 | blue;
	return (rgb);
}

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
	light = sous_vec(map->tab->spot, inter);
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
	double	intensity;
	t_vec	inter;
	double 	refl;

	inter = intersection(sphere, ray, map->tab->cam.pos);
	light = sous_vec(map->tab->spot, inter);
	norm = get_normal_sphere(sphere, ray, map);
	refl = 2.0 * (dot_vec(norm, light));
	if ((dot_vec(norm, light)) > 0.0 && refl > 0.0)
	{
		half = add_vec(ray, light);
		tmp = fmax(dot_vec(norm, half), 0.0);
		intensity = pow(tmp, 0.4);
		return (reflection(rgb, intensity));
	}
	return (rgb);
}


int	sphere_lumos(t_map *map, t_sphere *sphere, t_vec ray)
{
	int	diffuse;
	int	spec;
	int	rgb;

	rgb = sphere->rgb;
	spec = sphere_lumos_spec(map, sphere, ray, rgb);
	diffuse = sphere_lumos_diff(map, sphere, ray, spec);
	return (diffuse);
}
