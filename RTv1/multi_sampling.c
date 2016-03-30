/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_sampling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 14:16:55 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/30 14:40:01 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	nearest_obj_n(t_map *map, t_vec ray, t_vec org, void **st)
{
	st[0] = nearest_sphere(ray, map, 1, org);
	st[1] = nearest_plan(org, ray, map);
	st[2] = nearest_cyl(ray, map, 1, org);
	st[3] = nearest_cone(ray, map, 1, org);
}

void	multi_sampling(int x, int y, t_map *map)
{
	int		i;
	int		color[8];
	t_vec	ray[3];
	void	*st[NB_OBJ];
	void	*small;

	i = 0;
	while (i < 8)
	{
		color[i] = 0x000000;
		ray[0] = init_ray(map, (double)x +
				(0.125 * i), (double)y + (0.125 * i));
		nearest_obj_n(map, ray[0], map->tab->cam.pos, st);
		small = smaller_void(st);
		if ((small = smaller_void(st)) != NULL)
			color[i] = multi_spot(st, small, ray, map);
		i++;
	}
	pixel_put(map, x, y, moy_rgb(color, 8));
}
