/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lumos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 14:56:20 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/18 12:34:14 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		reflection(int rgb, double dot)
{
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
	double			dif;

	if (dot > 0.01)
		return (rgb);
	red = (rgb & 0xFF0000) >> 16;
	green = (rgb & 0xFF00) >> 8;
	blue = rgb & 0xFF;
	dif = (((dot) * (2.0 - 0.2)) / 0.01) + 0.2;
	red = (red + (0xFF / dif)) / 2;
	blue = (blue + (0xFF / dif)) / 2;
	green = (green + (0xFF / dif)) / 2;
	red = red < (rgb & 0xFF0000) >> 16 ? (rgb & 0xFF0000) >> 16 : red;
	green = green < (rgb & 0xFF00) >> 8 ? (rgb & 0xFF00) >> 8 : green;
	blue = blue < (rgb & 0xFF) ? (rgb & 0xFF) : blue;
	red = red > 255 ? 255 : red;
	blue = blue > 255 ? 255 : blue;
	green = green > 255 ? 255 : green;
	rgb = red << 16 | green << 8 | blue;
	return (rgb);
}

int		moyenne(int *n, int len)
{
	int nb;
	int i;

	if (len == 0)
		return (0);
	i = 0;
	nb = 0;
	while (i < len)
	{
		nb += n[i];
		i++;
	}
	nb /= len;
	return (nb);
}

int		moy_rgb(int *rgb, int len)
{
	int	red[len];
	int	green[len];
	int	blue[len];
	int i;

	i = 0;
	while (i < len)
	{
		red[i] = (rgb[i] & 0xFF0000) >> 16;
		green[i] = (rgb[i] & 0xFF00) >> 8;
		blue[i] = rgb[i] & 0xFF;
		i++;
	}
	red[0] = moyenne(red, len);
	blue[0] = moyenne(blue, len);
	green[0] = moyenne(green, len);
	red[0] = red[0] > 255 ? 255 : red[0];
	blue[0] = blue[0] > 255 ? 255 : blue[0];
	green[0] = green[0] > 255 ? 255 : green[0];
	i = red[0] << 16 | green[0] << 8 | blue[0];
	return (i);
}

t_vec	get_light_ray(void *obj, t_vec ray, t_vec spot, t_map *map)
{
	t_vec light;

	light = sous_vec(spot, intersection(obj, ray, map->tab->cam.pos));
	return (light);
}


int		multi_spot(void **st, void *small, t_vec rays[3], t_map *map)
{
	int     i;
	int     tmp;
	t_vec   inter;
	int     rgb[map->tab->nb_spot];
	t_vec	ray;

	ray = rays[0];
	i = 0;
	inter = intersection(small, ray, map->tab->cam.pos);
	while (i < map->tab->nb_spot)
	{
		rgb[i] = *(int*)(small + sizeof(double));
		map->tab->spot_a = &(map->tab->spot[i]);
		if (small == st[0])
			rgb[i] = sphere_lumos(map, small, ray, rgb[i]);
		else if (small == st[2])
			rgb[i] = cyl_lumos(map, small, ray, rgb[i]);
		else if (small == st[3])
			rgb[i] = cyl_lumos(map, small, ray, rgb[i]);
		//    else if (small == st[1])
		//        tmp = plan_lumos(map, small, ray, tmp);
		rays[1] = sous_vec_n(*map->tab->spot_a, inter);
		if (!(shadow(map, small, rays, *map->tab->spot_a)))
			rgb[i] = get_shadow(map, small, rays, rgb[i]);
		i++;
	}
	tmp = moy_rgb(rgb, map->tab->nb_spot);
	return (tmp);
}
