/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 19:55:28 by Client            #+#    #+#             */
/*   Updated: 2016/02/28 14:24:46 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	*plan(t_map *map, int x, int y)
{
	t_vec	nor;
	double	t;
	t_vec	ray;

	ray = init_ray(map, x, y);
	nor.x = 0.0;
	nor.y = -1.0;
	nor.z = 0.0;
	t = -(((nor.x * (map->tab->cam.pos.x - 0.0)) +
			(nor.y * (map->tab->cam.pos.y - 0.0)) +
			 (nor.z * (map->tab->cam.pos.z - 0.0)))
			/ ((nor.x * ray.x) + (nor.y * ray.y) + (nor.z * ray.z)));
	if (t < 0.0)
		return (NULL);
	map->tab->plan.t = t;
	return ((void*)&(map->tab->plan));
}
