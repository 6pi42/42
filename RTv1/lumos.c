/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lumos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 14:56:20 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/30 15:30:12 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

struct s_tab_f	lumos_spec[] = {
	{&sphere_lumos_spec},
	{0x0},
	{&cyl_lumos_spec},
	{&cone_lumos_spec},
};

struct s_tab_f	lumos_diff[] = {
	{&sphere_lumos_diff},
	{&plan_lumos},
	{&cyl_lumos_diff},
	{&cone_lumos_diff},
};

int		mul_rgb(int rgb, double coef)
{
	int	red;
	int	green;
	int	blue;

	red = ((rgb & 0xFF0000) >> 16) * coef;
	green = ((rgb & 0xFF00) >> 8) * coef;
	blue = (rgb & 0xFF) * coef;
	red = red > 0xFF ? 0xFF : red;
	green = green > 0xFF ? 0xFF : green;
	blue = blue > 0xFF ? 0xFF : blue;
	return (red << 16 | green << 8 | blue);
}

int		specular(int rgb, int lumos, double dot)
{
	int	red;
	int	blue;
	int	green;

	lumos = mul_rgb(lumos, dot);
	red = ((rgb & 0xFF0000) >> 16) + ((lumos & 0xFF0000) >> 16);
	green = ((rgb & 0xFF00) >> 8) + ((lumos & 0xFF00) >> 8);
	blue = (rgb & 0xFF) + (lumos & 0xFF);
	red = red > 0xFF ? 0xFF : red;
	blue = blue > 0xFF ? 0xFF : blue;
	green = green > 0xFF ? 0xFF : green;
	return (red << 16 | green << 8 | blue);
}

int		multi_spot(void **st, void *small, t_vec rays[3], t_map *map)
{
	t_vec	inter;
	int		rgb[map->tab->nb_spot];
	int		i;
	int		j;

	i = 0;
	j = 0;
	inter = intersection(small, rays[0], map->tab->cam.pos);
	while (j < map->tab->nb_spot && small != NULL)
	{
		rgb[j] = *(int*)(small + sizeof(double));
		map->tab->spot_a = &(map->tab->spot[j]);
		rays[1] = sous_vec(*map->tab->spot_a, inter);
		while (small != st[i] && i < NB_OBJ)
			i++;
		if (!(shadow(map, small, rays, *map->tab->spot_a)))
			rgb[j] = get_shadow(map, small, rays, rgb[j]);
		else if (i != 1)
			rgb[j] = lumos_spec[i].f(map, small, inter, rgb[j]);
		rgb[j] = lumos_diff[i].f(map, small, inter, rgb[j]);
		j++;
	}
	return (moy_rgb(rgb, map->tab->nb_spot));
}
