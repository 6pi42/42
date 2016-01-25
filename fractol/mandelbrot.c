/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbroot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Br: cborer <cborer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/23 13:41:11 br cborer            #+#    #+#             */
/*   Updated: 2016/01/25 16:02:07 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mandelbrot(t_map *map)
{
	t_comp	comp;
	int		x;
	int		y;
	int		iter;
	t_comp	comptmp;
	t_comp	comp2;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			comp.r = 1.5 * (x - map->mouse.x / 2) / (0.5 * map->zoom * WIDTH);
			comp.i = 1.5 * (y - map->mouse.y / 2) / (0.5 * map->zoom * HEIGHT);
			comp2.i = 0.0;
			comp2.r = 0.0;
			iter = 0;
			while(iter < map->max_iter)
			{
				iter++;
				comptmp.r = comp2.r * comp2.r - comp2.i * comp2.i + comp.r;
				comp2.i = 2 * comp2.r * comp2.i + comp.i;
				comp2.r = comptmp.r;
				if (comp2.r * comp2.r + comp2.i * comp2.i > 4)
					break ;
			}
			pixel_put(map, x, y, 256 * 256 * (256 - iter * 10)
				+ 256 + (256 - iter) + (256 - iter));
			x++;
		}
		y++;
	}
}
