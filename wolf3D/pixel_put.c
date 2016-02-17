/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 12:16:27 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/12 15:30:50 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	pixel_put(t_map *map, int x, int y, int color)
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
	unsigned int	color_value;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	color_value = mlx_get_color_value(map->e.mlx, color);
	red = (color_value & 0xFF0000) >> 16;
	green = (color_value & 0xFF00) >> 8;
	blue = (color_value & 0xFF);
	map->img.data[y * map->img.size_line + (x * map->img.bpp) / 8] = blue;
	map->img.data[y * map->img.size_line + (x * map->img.bpp) / 8 + 1] = green;
	map->img.data[y * map->img.size_line + (x * map->img.bpp) / 8 + 2] = red;
}

void	init_img(t_map *map, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			if (j < 640 && i < 200)
				pixel_put(map, j, i,map->sky[i][j]);
			else
				pixel_put(map, j, i, color);
			j++;
		}
		i++;
	}
}
