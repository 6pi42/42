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
	t_comp	comp;
	int		y;
	int		x;
	int		iter;
	t_comp	comptmp;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			comp.r = 1.5 * (x - map->mouse.x / 2) / (0.5 * map->zoom * WIDTH);
			comp.i = 1.5 * (y - map->mouse.y / 2) / (0.5 * map->zoom * HEIGHT);
			iter = 0;
			while(iter < MAX_ITER)
			{
				iter++;
				comptmp = comp;
				comp.r = comptmp.r * comptmp.r - comptmp.i * comptmp.i + map->julia.r;
				comp.i = 2 * comptmp.r * comptmp.i + map->julia.i;
				if (comp.r * comp.r + comp.i * comp.i > 4)
					break ;
			}
			//pixel_put(map, x, y, 256 * 256 * (256 - iter * 10)
			//	+ 256 + (256 - iter) + (256 - iter));
			pixel_put(map, x, y, iter % 360 - iter * iter);
			x++;
		}
		y++;
	}
}
