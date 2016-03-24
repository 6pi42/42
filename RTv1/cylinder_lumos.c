/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_lumos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 13:33:22 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/24 13:32:44 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		cyl_lumos_diff(t_map *map, void *obj, t_vec inter, int rgb)
{
	t_vec	light;
	double	angle;
	t_vec	org;
	t_cone	*cyl;

	cyl = (t_cone*)obj;
	org = *map->tab->spot_a;
	light = sous_vec(inter, org);
	angle = fmax(dot_vec(light, cyl->norm), 0.0);
	rgb = light_rgb(rgb, angle);
	return (rgb);
}

int		cyl_lumos_spec(t_map *map, void *obj, t_vec inter, int rgb)
{
	t_vec	light;
	t_vec	half;
	double	dot;
	t_cone	*cyl;
	t_vec	eye;

	cyl = (t_cone*)obj;
	eye = sous_vec(inter, map->tab->cam.pos);
	light = sous_vec(inter, *map->tab->spot_a);
	half = add_vec(eye, light);
	dot = fmax(0.0, dot_vec(half, cyl->norm));
	dot = pow(dot, 16.0);
	return (specular(rgb, 0xFFFFFF, dot));
}
