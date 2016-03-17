/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_lumos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 12:45:15 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/17 13:26:07 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		cone_lumos_diff(t_map *map, t_cone *cone, t_vec ray, int rgb)
{
	t_vec	light;
	double	angle;
	t_vec	inter;
	t_vec	org;

	org = *map->tab->spot_a;
	inter = intersection(cone, ray, map->tab->cam.pos);
	light = sous_vec(org, inter);
	angle = acos(dot_vec(light, cone->norm));
	if (angle <= 0)
		rgb = 0x000000;
	else
		rgb = light_rgb(rgb, angle * 0.6);
	return (rgb);
}

int		cone_lumos_spec(t_map *map, t_cone *cone, t_vec ray, int rgb)
{
	t_vec	light;
	t_vec	half;
	double	tmp;
	double	intensity;
	t_vec	inter;
	double 	refl;

	inter = intersection(cone, ray, map->tab->cam.pos);
	light = sous_vec(*map->tab->spot_a, inter);
	refl = 2.0 * (dot_vec(cone->norm, light));
	if ((dot_vec(cone->norm, light)) > 0.0 && refl > 0.0)
	{
		half = add_vec(ray, light);
		tmp = fmax(dot_vec(cone->norm, half), 0.0);
		intensity = pow(tmp, 0.4);
		return (reflection(rgb, intensity));
	}
	return (rgb);
}

int	cone_lumos(t_map *map, t_cone *cone, t_vec ray, int rgb)
{
	rgb = cone_lumos_diff(map, cone, ray, rgb);
	rgb = cone_lumos_spec(map, cone, ray, rgb);
	return (rgb);
}
