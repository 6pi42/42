/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 12:35:47 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/22 13:34:47 by cboyer           ###   ########.fr       */
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

int			add_rgb(int rgb)
{
	int	red;
	int	green;
	int	blue;
	int	ret;

	red = (rgb & 0xFF0000) >> 16;
	green = (rgb & 0xFF00) >> 8;
	blue = rgb & 0xFF;
	ret = blue + green + blue;
	return (ret);
}

int			max_rgb(int *rgb, int len)
{
	int	max;
	int	i;
	int	score[len];
	int	tmp;
	int	equal;

	if (len == 0)
		return (0);
	equal = 0;
	i = 0;
	tmp = -1;
	max = -1;
	while (i < len)
	{
		score[i] = add_rgb(rgb[i]);
		if (score[i] > tmp)
		{
			tmp = score[i];
			max = rgb[i];
			equal++;
		}
		i++;
	}
	return (max);
}

int			min_rgb(int *rgb, int len)
{
	int	max;
	int	i;
	int	score[len];
	int	tmp;
	int	equal;

	if (len == 0)
		return (0);
	equal = 0;
	i = 0;
	tmp = -1;
	max = -1;
	while (i < len)
	{
		score[i] = add_rgb(rgb[i]);
		if (tmp == -1 || score[i] < tmp)
		{
			tmp = score[i];
			max = rgb[i];
			equal++;
		}
		i++;
	}
	return (max);
}
