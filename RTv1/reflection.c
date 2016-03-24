/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 14:02:22 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/24 13:33:53 by cboyer           ###   ########.fr       */
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
