/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 19:55:28 by Client            #+#    #+#             */
/*   Updated: 2016/03/05 12:51:47 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec	get_norm_plan(t_plan *plan, t_vec ray, t_map *map)
{
	t_vec norm;

	(void)plan;
	(void)ray;
	(void)map;
	norm.x = 0.0;
	norm.y = 1.0;
	norm.z = 0.0;
	return (norm);
}

void	*plan(t_vec org, t_vec ray, t_map *map)
{
	t_vec	nor;
	double	t;

	nor = get_norm_plan(&map->tab->plan, ray, map);
	t = -(((nor.x * (org.x - 0.0)) +
			(nor.y * (org.y - 0.0)) +
			(nor.z * (org.z - 0.0)))
			/ ((nor.x * ray.x) + (nor.y * ray.y) + (nor.z * ray.z)));
	if (t < 0.0)
		return (NULL);
	map->tab->plan.t = t;
	return ((void*)&(map->tab->plan));
}

int		plan_lumos(t_map *map, t_plan *plan, t_vec ray)
{
	int		rgb;
	t_vec	light;
	double	angle;
	t_vec	norm;

	light = get_light_ray((void*)plan, ray, map);
	norm = get_norm_plan(plan, ray, map);
	angle = acos(dot_vec(light, norm));
	if (angle <= 0)
		rgb = 0x000000;
	else
		rgb = light_rgb(plan->rgb, angle * 0.6);
	return (rgb);
}
