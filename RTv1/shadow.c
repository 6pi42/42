/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 15:10:23 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/09 18:32:32 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec	get_light_ray(void *obj, t_vec ray, t_map *map, t_vec spot)
{
	t_vec	light;
	double	t;

	t = *(double*)obj;
	light.x = (map->tab->cam.pos.x + ray.x * t) - spot.x;
	light.y = (map->tab->cam.pos.y + ray.y * t) - spot.y;
	light.z = (map->tab->cam.pos.z + ray.z * t) - spot.z;
	normalize_vec(&light);
	return (light);
}

int	shadow(t_map *map, void *obj, t_vec light, t_vec spot)
{
	void	*st[NB_OBJ];
	void	*small;

	nearest_obj(map, light, spot, st);
	small = smaller_void(st);
	if (small != NULL && small == obj)
		return (1);
	return (0);
}

int	light_rgb(int rgb, double angle)
{
	int	red;
	int	green;
	int	blue;

	red = (rgb & 0xFF0000) >> 16;
	green = (rgb & 0xFF00) >> 8;
	blue = rgb & 0xFF;
	red *= angle;
	blue *= angle;
	green *= angle;
	red = red > 255 ? 255 : red;
	blue = blue > 255 ? 255 : blue;
	green = green > 255 ? 255 : green;
	rgb = red << 16 | green << 8 | blue;
	return (rgb);
}

int	add_rgb(int rgb, double coef)
{
	int	red;
	int	green;
	int	blue;

	red = (rgb & 0xFF0000) >> 16;
	green = (rgb & 0xFF00) >> 8;
	blue = rgb & 0xFF;
	red += coef;
	blue += coef;
	green += coef;
	red = red > 255 ? 255 : red;
	blue = blue > 255 ? 255 : blue;
	green = green > 255 ? 255 : green;
	rgb = red << 16 | green << 8 | blue;
	return (rgb);
}
