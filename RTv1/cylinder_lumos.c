/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_lumos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 13:33:22 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/22 14:11:48 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		cyl_lumos_diff(t_map *map, void *obj, t_vec ray, int rgb)
{
	t_vec	light;
	double	angle;
	t_vec	inter;
	t_vec	org;
	t_cone	*cyl;

	cyl = (t_cone*)obj;
	org = *map->tab->spot_a;
	inter = intersection(cyl, ray, map->tab->cam.pos);
	light = sous_vec(inter, org);
	angle = dot_vec(light, cyl->norm);
	if (angle <= 0)
		rgb = 0x000000;
	else
		rgb = light_rgb(rgb, angle);
	return (rgb);
}

int		cyl_lumos_spec(t_map *map, void *obj, t_vec ray, int rgb)
{
	t_vec	light;
	t_vec	half;
	t_vec	inter;
	double	dot;
	t_cone	*cyl;

	cyl = (t_cone*)obj;
	inter = intersection(cyl, ray, map->tab->cam.pos);
	light = sous_vec(*map->tab->spot_a, inter);
	half = add_vec(cyl->norm, light);
	dot = fmax(dot_vec(cyl->norm, half), 0.0);
	dot = pow(dot, 2.0);
	return (reflection(rgb, dot));
}
