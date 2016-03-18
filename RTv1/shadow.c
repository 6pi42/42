/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 15:10:23 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/18 15:11:07 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
/*
int	compare_vec(t_vec a, t_vec b, t_vec spot, t_vec org)
{
	if (a.x >= b.x && spot.x >= org.x && a.y >= b.y && spot.y >= org.y && a.z >= b.z && spot.z >= org.z)
		return (1);
	if (a.x <= b.x && spot.x <= org.x && a.y <= b.y && spot.y <= org.y && a.z <= b.z && spot.z <= org.z)
		return (1);
	return (0);
}*/

int	shadow(t_map *map, void *obj, t_vec ray[3], t_vec spot)
{
	void	*st[NB_OBJ];
	void	*small;

	nearest_obj(map, ray[1], spot, st);
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
