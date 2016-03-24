/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 12:35:47 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/24 13:46:35 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
