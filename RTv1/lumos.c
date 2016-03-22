/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lumos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 14:56:20 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/22 15:00:24 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

struct s_tab_f	lumos_spec[] = {
	{&sphere_lumos_spec},
	{0x0},
	{&cyl_lumos_spec},
	{&cyl_lumos_spec},
};

struct s_tab_f	lumos_diff[] = {
	{&sphere_lumos_diff},
	{&plan_lumos},
	{&cyl_lumos_diff},
	{&cyl_lumos_diff},
};

int		reflection(int rgb, double dot)
{
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
	double			dif;

	if (dot > 0.05)
		return (rgb);
	red = (rgb & 0xFF0000) >> 16;
	green = (rgb & 0xFF00) >> 8;
	blue = rgb & 0xFF;
	dif = (((dot) * (2.0 - 0.0)) / 0.01) + 0.0;
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

int		multi_spot(void **st, void *small, t_vec rays[3], t_map *map)
{
	int		i[3];
	t_vec	inter;
	int		rgb[map->tab->nb_spot];

	i[1] = 0;
	i[0] = -1;
	i[2] = 0;
	inter = intersection(small, rays[0], map->tab->cam.pos);
	while (i[0]++ < map->tab->nb_spot - 1)
	{
		rgb[i[0]] = *(int*)(small + sizeof(double));
		map->tab->spot_a = &(map->tab->spot[i[0]]);
		rays[1] = sous_vec(*map->tab->spot_a, inter);
		while (small != st[i[1]] && i[1] < NB_OBJ)
			i[1]++;
		if (!(shadow(map, small, rays, *map->tab->spot_a)) && (i[2] = i[2] + 1))
			rgb[i[0]] = get_shadow(map, small, rays, rgb[i[0]]);
		else if (i[1] != 1)
			rgb[i[0]] = lumos_spec[i[1]].f(map, small, rays[0], rgb[i[0]]);
		rgb[i[0]] = lumos_diff[i[1]].f(map, small, rays[0], rgb[i[0]]);
	}
	rgb[0] = i[2] ? moy_rgb(rgb, map->tab->nb_spot) :
		max_rgb(rgb, map->tab->nb_spot);
	return (rgb[0]);
}
