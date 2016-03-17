/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soft_shadow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 12:39:41 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/17 13:52:59 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec	init_lightpos(t_vec lightpos)
{
	t_vec light;

	light.x = lightpos.x - 20.0;
	light.y = lightpos.y;
	light.z = lightpos.z - 20.0;
	return (light);
}

t_vec	get_lightpos(t_vec lightpos, double off_x, double off_y)
{
	t_vec light;

	light = init_lightpos(lightpos);
	light.x += off_x;
	light.z += off_y;
	return (light);
}

int		get_shadow_color(int color, int nb)
{
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
	double			dif;

	dif = (((nb) * (1.4 - 0.4)) / 256.0) + 0.4;
	red = (color & 0xFF0000) >> 16;
	green = (color & 0xFF00) >> 8;
	blue = color & 0xFF;
	red *= dif;
	blue *= dif;
	green *= dif;
	red = red > 255 ? 255 : red;
	blue = blue > 255 ? 255 : blue;
	green = green > 255 ? 255 : green;
	return (red << 16 | green << 8 | blue);
}

double	rand_double(void)
{
	return (rand() / (RAND_MAX / (2.5)));
}

int		get_shadow(t_map *map, void *obj, t_vec inter, int rgb)
{
	t_pos		pos;
	int			count;
	t_vec		offset;
	t_vec		light;

	pos.y = -1;
	count = 0;
	return (get_shadow_color(rgb, 0));
	while (++pos.y < 16)
	{
		pos.x = -1;
		while (++pos.x < 16)
		{
			offset.x = (pos.x * 2.5) + rand_double();
			offset.y = (pos.y * 2.5) + rand_double();
			light = get_lightpos(*map->tab->spot_a, offset.x, offset.y);
			if (shadow(map, obj, sous_vec(light, inter), light))
				count++;
		}
	}
	return (get_shadow_color(rgb, count));
}
