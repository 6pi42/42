/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/23 13:18:11 by cboyer            #+#    #+#             */
/*   Updated: 2016/01/24 15:41:40 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	julia(t_map *map)
{
	t_comp	c[2];
	int		iter[3];

	iter[1] = 0;
	while (++iter[1] < HEIGHT)
	{
		iter[0] = 0;
		while (++iter[0] < WIDTH)
		{
			c[0].r = 1.5 * (iter[0] - map->mouse.x / 2) /
			(0.5 * map->zoom * WIDTH);
			c[0].i = 1.5 * (iter[1] - map->mouse.y / 2) /
			(0.5 * map->zoom * HEIGHT);
			iter[2] = 0;
			while(++iter[2] < MAX_ITER)
			{
				c[1] = c[0];
				c[0].r = c[1].r * c[1].r - c[1].i * c[1].i + map->julia.r;
				c[0].i = 2 * c[1].r * c[1].i + map->julia.i;
				if (c[0].r * c[0].r + c[0].i * c[0].i > 4)
					break ;
			}
			pixel_put(map, iter[0], iter[1], 256 * 256 * (256 - iter[2] * 10)
				+ 256 + (256 - iter[2]) + (256 - iter[2]));
		}
	}
}
