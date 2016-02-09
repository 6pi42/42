/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   siegel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/31 16:31:30 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/09 15:54:33 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	siegel(t_map *map)
{
	t_comp	c[2];
	int		i[3];

	i[1] = 0;
	while (++i[1] < HEIGHT)
	{
		i[0] = 0;
		while (++i[0] < WIDTH)
		{
			c[0].r = 1.5 * (i[0] - map->mouse.x / 2) / (map->zoom * WIDTH / 2);
			c[0].i = 1.5 * (i[1] - map->mouse.y / 2) / (map->zoom * HEIGHT / 2);
			i[2] = 0;
			while (++i[2] < map->max_iter)
			{
				c[1] = c[0];
				c[0].r = c[1].r * c[1].r - c[1].i * c[1].i - 0.39;
				c[0].i = 2 * c[1].r * c[1].i - 0.58;
				if (c[0].r * c[0].r + c[0].i * c[0].i > 4)
					break ;
			}
			pixel_put(map, i[0], i[1], !map->c ? get_c(i[2]) : get_c2(i[2]));
		}
	}
}
