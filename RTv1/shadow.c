/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 15:10:23 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/22 13:35:12 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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

int	shadow_rgb(int rgb, double angle)
{
	int	red;
	int	green;
	int	blue;

	red = (rgb & 0xFF0000) >> 16;
	green = (rgb & 0xFF00) >> 8;
	blue = rgb & 0xFF;
	if (angle == 0)
		return (0);
	red /= angle;
	blue /= angle;
	green /= angle;
	red = red < 0 ? 0 : red;
	blue = blue < 0 ? 0 : blue;
	green = green < 0 ? 0 : green;
	rgb = red << 16 | green << 8 | blue;
	return (rgb);
}
