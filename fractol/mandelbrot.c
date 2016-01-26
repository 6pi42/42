/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbroot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Br: cborer <cborer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/23 13:41:11 br cborer            #+#    #+#             */
/*   Updated: 2016/01/25 16:02:07 bi[1] cboi[1]er           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mandelbrot(t_map *map)
{
	t_comp	c[3];
	int		i[3];

	i[1] = 0;
	while (++i[1] < HEIGHT)
	{
		i[0] = 0;
		while (++i[0] < WIDTH)
		{
			c[0].r = 1.5 * (i[0] - map->mouse.x / 2) / (map->zoom * WIDTH / 2);
			c[0].i = 1.5 * (i[1] - map->mouse.y / 2) / (map->zoom * HEIGHT / 2);
			c[1].i = 0.0;
			c[1].r = 0.0;
			i[2] = 0;
			while(++i[2] < map->max_iter)
			{
				c[2].r = c[1].r * c[1].r - c[1].i * c[1].i + c[0].r;
				c[1].i = 2 * c[1].r * c[1].i + c[0].i;
				c[1].r = c[2].r;
				if (c[1].r * c[1].r + c[1].i * c[1].i > 4)
					break ;
			}
			pixel_put(map, i[0], i[1], 256 * 256 * (256 - i[2] * 10)
				+ 256 + (256 - i[2]) + (256 - i[2]));
		}
	}
}
