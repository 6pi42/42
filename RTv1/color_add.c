/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diff_spec_shade_add.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 13:46:09 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/24 14:02:02 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	moyenne(int *n, int len)
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

int			moy_rgb(int *rgb, int len)
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
