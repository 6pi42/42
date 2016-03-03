/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lumos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 13:31:21 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/03 16:17:46 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		light_rgb(int rgb, double angle)
{
	int	red;
	int	green;
	int	blue;

	red = (rgb >> 16) & 0xFF;
	green = (rgb >> 8) & 0xFF;
	blue = rgb & 0xFF;
	red /= angle;
	blue /= angle;
	green /= angle;
	rgb = red;
	rgb = (rgb << 8) + green;
	rgb = (rgb << 8) + blue;
	return (rgb);
}

int		shadow_rgb(int rgb, double angle)
{
	int	red;
	int	green;
	int	blue;

	red = (rgb >> 16) & 0xFF;
	green = (rgb >> 8) & 0xFF;
	blue = rgb & 0xFF;
	red /= angle;
	blue /= angle;
	green /= angle;
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

	(void)obj;
	(void)map;
	(void)x;
	(void)y;
	(void)st;
	rgb = 0xFF0000;
	return (rgb);
}
