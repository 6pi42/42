/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 17:03:27 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/17 17:34:46 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	pixel_put_mmap(t_map *map, int x, int y, int color)
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
	map->mmap.data[y * map->img.size_line + (x * map->img.bpp) / 8] = blue;
	map->mmap.data[y * map->img.size_line + (x * map->img.bpp) / 8 + 1] = green;
	map->mmap.data[y * map->mmap.size_line + (x * map->img.bpp) / 8 + 2] = red;
}

static void	draw_rect(int i, int j)
{
	int	y;
	int	x;

	y = i + 10;
	x = j + 10;

}

void		mini_map(t_map *map)
{
	int	i;
	int	j;

	if (!(map->mmap.img = mlx_new_image(map->e.mlx, 100, 100)))
		ft_error();
	i = (int)map->player.pos.y - 5;
	while (i < (int)map->player.pos.y + 5)
	{
		j = (int)map->player.pos.x - 5;
		while (j < (int)map->player.pos.x - 5)
		{
			j++;
		}
		i++;
	}
}
