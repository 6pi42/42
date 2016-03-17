/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_lumos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 13:33:22 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/17 17:03:03 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		cyl_lumos_diff(t_map *map, t_cone *cyl, t_vec ray, int rgb)
{
	t_vec	light;
	double	angle;
	t_vec	inter;
	t_vec	org;

	org = *map->tab->spot_a;
	inter = intersection(cyl, ray, map->tab->cam.pos);
	light = sous_vec(org, inter);
	angle = acos(dot_vec(light, cyl->norm));
	if (angle <= 0)
		rgb = 0x000000;
	else
		rgb = light_rgb(rgb, angle * 0.6);
	return (rgb);
}

int		cyl_lumos_spec(t_map *map, t_cone *cyl, t_vec ray, int rgb)
{
	t_vec	light;
	t_vec	half;
	t_vec	inter;
	double	dot;

	inter = intersection(cyl, ray, map->tab->cam.pos);
	light.x = inter.x - map->tab->spot_a->x;
	light.y = inter.y - map->tab->spot_a->y;
	light.z = inter.z - map->tab->spot_a->z;
	normalize_vec(&light);
	half.x = cyl->norm.x + light.x;
	half.y = cyl->norm.y + light.y;
	half.z = cyl->norm.z + light.z;
	normalize_vec(&half);
	dot = fmax(dot_vec(cyl->norm, half), 0.0);
	dot = pow(dot, 2.0);
	return (reflection(rgb, dot));
}

int		cyl_lumos(t_map *map, t_cone *cyl, t_vec ray, int rgb)
{
	rgb = cyl_lumos_diff(map, cyl, ray, rgb);
	rgb = cyl_lumos_spec(map, cyl, ray, rgb);
	return (rgb);
}
