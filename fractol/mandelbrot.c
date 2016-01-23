/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbroot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Br: cborer <cborer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/23 13:41:11 br cborer            #+#    #+#             */
/*   Updated: 2016/01/23 15:15:21 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mandelbrot(t_map *map, int max_iter)
{
	t_comp	comp;
	int		i;
	int		j;
	int		iter;
	t_comp	comptmp;
	t_comp	comp2;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			comp.i = 1.5 * (i - WIDTH / 2) / (0.5 * map->zoom * WIDTH);
			comp.r = 1.5 * (j - HEIGHT / 2) / (0.5 * map->zoom * HEIGHT);
			comp2.i = 0.0;
			comp2.r = 0.0;
			iter = 0;
			while(iter < max_iter)
			{
				iter++;
				comptmp.r = comp2.r * comp2.r - comp2.i * comp2.i + comp.r;
				comp2.i = 2 * comp2.r * comp2.i + comp.i;
				comp2.r = comptmp.r;
				if (comp2.r * comp2.r + comp2.i * comp2.i > 4)
					break ;
			}
			pixel_put(map, j, i, 256 * 256 * (256 - iter * 10)
				+ 256 + (256 - iter) + (256 - iter));
			j++;
		}
		i++;
	}
}
