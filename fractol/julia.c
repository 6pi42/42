/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/23 13:18:11 by cboyer            #+#    #+#             */
/*   Updated: 2016/01/23 16:19:14 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	julia(t_map *map, int max_iter)
{
	t_comp	comp;
	int		i;
	int		j;
	int		iter;
	t_comp	comptmp;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			comp.i = 1.5 * (i - WIDTH / 2) / (0.5 * map->zoom * WIDTH);
			comp.r = 1.5 * (j - HEIGHT / 2) / (0.5 * map->zoom * HEIGHT);
			iter = 0;
			while(iter < max_iter)
			{
				iter++;
				comptmp = comp;
				comp.r = comptmp.r * comptmp.r - comptmp.i * comptmp.i + map->julia.r;
				comp.i = 2 * comptmp.r * comptmp.i + map->julia.i;
				if (comp.r * comp.r + comp.i * comp.i > 4)
					break ;
			}
			pixel_put(map, j, i, 256 * 256 * (256 - iter * 10)
				+ 256 + (256 - iter) + (256 - iter));
			j++;
		}
		i++;
	}
}
