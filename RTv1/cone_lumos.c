/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_lumos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 12:45:15 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/16 12:47:01 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		cone_lumos_diff(t_map *map, t_cone *cone, t_vec ray, t_vec org)
{
	int		rgb;
	t_vec	light;
	double	angle;
	t_vec	inter;

	inter = intersection(cone, ray, map->tab->cam.pos);
	light = sous_vec(org, inter);
	angle = acos(dot_vec(light, cone->norm));
	if (angle <= 0)
		rgb = 0x000000;
	else
		rgb = light_rgb(cone->rgb, angle * 0.6);
	return (rgb);
}

int	cone_lumos(t_map *map, t_cone *cone, t_vec ray, t_vec org)
{
	int	diffuse;
	//int	spec;

	diffuse = cone_lumos_diff(map, cone, ray, org);
	//spec = cyl_lumos_spec(map, sphere, ray, org);
	return (diffuse);
}
