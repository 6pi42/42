/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_lumos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 13:33:22 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/15 14:15:11 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		cyl_lumos_diff(t_map *map, t_cone *cyl, t_vec ray, t_vec org)
{
	int		rgb;
	t_vec	light;
	double	angle;

	light = get_light_ray((void*)cyl, ray, map, org);
	angle = acos(dot_vec(light, cyl->norm));
	if (angle <= 0)
		rgb = 0x000000;
	else
		rgb = light_rgb(cyl->rgb, angle * 0.6);
	return (rgb);
}

int	cyl_lumos(t_map *map, t_cone *cyl, t_vec ray, t_vec org)
{
	int	diffuse;
	//int	spec;

	diffuse = cyl_lumos_diff(map, cyl, ray, org);
	//spec = cyl_lumos_spec(map, sphere, ray, org);
	return (diffuse);
}
