/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 11:25:59 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/11 15:30:53 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	init_tmp(t_comp *c, int *i)
{
	c->i = 0.0;
	c->r = 0.0;
	*i = 0;
}

void		burning_ship(t_map *map)
{
	t_comp	c[3];
	int		i[3];

	i[1] = 0;
	while (++i[1] < HEIGHT)
	{
		i[0] = 0;
		while (++i[0] < WIDTH)
		{
			c[0].i = 2.5 * (i[1] - map->mouse.y / 2) / (map->zoom * HEIGHT / 2);
			c[0].r = 2 * (i[0] - map->mouse.x / 2) / (map->zoom * WIDTH / 2);
			init_tmp(&c[1], &i[2]);
			while (++i[2] < map->max_iter)
			{
				c[1].r = fabs(c[1].r);
				c[1].i = fabs(c[1].i);
				c[2].r = c[1].r * c[1].r - c[1].i * c[1].i + c[0].r;
				c[1].i = 2 * c[1].r * c[1].i + c[0].i;
				c[1].r = c[2].r;
				if (c[1].r * c[1].r + c[1].i * c[1].i > 4)
					break ;
			}
			pixel_put(map, i[0], i[1], !map->c ? get_c(i[2]) : get_c2(i[2]));
		}
	}
}
