/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 15:10:23 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/03 15:44:51 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	shadow(t_map *map, void *obj, t_vec ray)
{
	t_vec	light;
	void	*st[NB_OBJ];

	light = get_light_ray(obj, ray, map);
	if (map->tab->nb_sphere > 0)
		st[0] = nearest_sphere(light, map, map->tab->sphere, map->tab->spot);
	st[1] = plan(map, ray);
	if (smaller_void(st) != obj)
		return (0);
	else
		return (1);
}
