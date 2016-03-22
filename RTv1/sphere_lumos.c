/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_lumos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 13:31:54 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/22 15:07:19 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec	get_normal_sphere(t_sphere *sphere, t_vec ray, t_map *map)
{
	t_vec norm;

	norm = sous_vec(sphere->pos, intersection(sphere, ray, map->tab->cam.pos));
	return (norm);
}

int		sphere_lumos_diff(t_map *map, void *obj, t_vec ray, int rgb)
{
	t_vec		light;
	double		angle;
	t_vec		inter;
	t_sphere	*sphere;
	t_vec		org;

	org = *map->tab->spot_a;
	sphere = (t_sphere*)obj;
	sphere->norm = get_normal_sphere(sphere, ray, map);
	inter = intersection(sphere, ray, map->tab->cam.pos);
	light = sous_vec(inter, org);
	angle = dot_vec(light, sphere->norm);
	if (angle <= 0)
		rgb = 0x000000;
	else
		rgb = light_rgb(rgb, angle);
	return (rgb);
}

int		sphere_lumos_spec(t_map *map, void *obj, t_vec ray, int rgb)
{
	t_vec		light;
	t_vec		half;
	t_vec		inter;
	double		dot;
	t_sphere	*s;

	s = (t_sphere*)obj;
	inter = intersection(s, ray, map->tab->cam.pos);
	light = sous_vec(*map->tab->spot_a, inter);
	half = add_vec(s->norm, light);
	dot = fmax(dot_vec(s->norm, half), 0.0);
	dot = pow(dot, 2.0);
	return (reflection(rgb, dot));
}
