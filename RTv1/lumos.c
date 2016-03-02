/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lumos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 13:31:21 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/02 16:19:44 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec	init_ray_lumos(t_map *map, int x, int y, void *obj)
{
	t_vec	ray;
	t_vec	ray2;

	init_ray(map, x, y);
	ray2.x = map->tab->spot.x + ray.x * (*(double*)obj);
	ray2.y = map->tab->spot.y + ray.y * (*(double*)obj);
	ray2.z = map->tab->spot.z + ray.z * (*(double*)obj);
	normalize_vec(&ray2);
	return (ray2);
}

int		shadow_rgb(int rgb)
{
	int	red;
	int	green;
	int	blue;

	red = (rgb >> 16) & 0xFF;
	green = (rgb >> 8) & 0xFF;
	blue = rgb & 0xFF;
	red *= 10;
	blue *= 10;
	green *= 10;
	rgb = red;
	rgb = (rgb << 8) + green;
	rgb = (rgb << 8) + blue;
	return (rgb);
}

int		light_rgb(int rgb)
{
	int	red;
	int	green;
	int	blue;

	red = (rgb >> 16) & 0xFF;
	green = (rgb >> 8) & 0xFF;
	blue = rgb & 0xFF;
	red /= 10;
	blue /= 10;
	green /= 10;
	rgb = red;
	rgb = (rgb << 8) + green;
	rgb = (rgb << 8) + blue;
	return (rgb);
	return (rgb);
}

int		lumos(void *obj, t_map *map, int x, int y)
{
	void	*st[NB_OBJ];
	int		rgb;

	rgb = *(int*)(obj + sizeof(double));
	if (map->tab->nb_sphere > 0)
		st[0] = nearest_sphere_spot(y, x, map, map->tab->sphere);
	st[1] = plan_lumos(map, x, y);
	if (smaller_void(st) == obj)
		rgb = light_rgb(rgb);
	else
		rgb = shadow_rgb(rgb);
	return (rgb);
}
