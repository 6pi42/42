/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lumos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 13:31:21 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/04 11:22:55 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
