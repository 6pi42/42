/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 15:10:23 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/04 13:39:21 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	shadow(t_map *map, void *obj, t_vec ray)
{
	t_vec	light;
	void	*st[NB_OBJ];

	light = get_light_ray(obj, ray, map);
	st[0] = nearest_sphere(light, map, map->tab->sphere, map->tab->spot);
	st[1] = plan(map, ray);
	st[2] = nearest_cyl(light, map, map->tab->cylinder, map->tab->spot);
	if (smaller_void(st) != obj)
		return (0);
	else
		return (1);
}
