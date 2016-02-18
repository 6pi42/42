/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 17:03:27 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/18 17:50:56 by cboyer           ###   ########.fr       */
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
	map->mmap.data[y * map->mmap.size_line + (x * map->mmap.bpp) / 8] = blue;
	map->mmap.data[y * map->mmap.size_line + (x * map->mmap.bpp) / 8 + 1] =
			green;
	map->mmap.data[y * map->mmap.size_line + (x * map->mmap.bpp) / 8 + 2] = red;
}

static void	draw_rect(t_map *map, int i, int j)
{
	int	y;
	int	x;
	int	maxx;
	int	maxy;

	y = i * 10;
	x = j * 10;
	maxx = x + 10;
	maxy = y + 10;
	while (y < maxy)
	{
		x = j * 10;
		while (x < maxx)
		{
			pixel_put_mmap(map, x, y, 0xFFFFFF);
			x++;
		}
		y++;
	}
}

static void	init_mmap(t_map *map)
{
	int	i;
	int	j;
	int	x;
	int	y;

	x = 0;
	y = 0;
	i = HEIGHT - 125;
	while (i < HEIGHT - 25)
	{
		j = WIDTH - 125;
		x = 0;
		while (j < WIDTH - 25)
		{
			pixel_put_mmap(map, x, y, get_hex_color(map, j, i) / 2);
			x++;
			j++;
		}
		y++;
		i++;
	}
}

static void	draw_player(t_map *map)
{
	int	i;
	int	j;

	i = 48;
	while (i < 52)
	{
		j = 48;
		while (j < 52)
		{
			pixel_put_mmap(map, j, i, 0xEDFF0C);
			j++;
		}
		i++;
	}
}

void		mini_map(t_map *map)
{
	int	i;
	int	j;
	int	x;
	int	y;

	if (!(map->mmap.img = mlx_new_image(map->e.mlx, 100, 100)))
		ft_error();
	map->mmap.data = mlx_get_data_addr(map->mmap.img, &(map->mmap.bpp),
			&(map->mmap.size_line), &(map->mmap.endian));
	init_mmap(map);
	y = (int)map->player.pos.y - 5 > 0 ? 0 : abs((int)map->player.pos.y - 5);
	x = (int)map->player.pos.x - 5 > 0 ? 0 : abs((int)map->player.pos.x - 5);
	j = (int)map->player.pos.x - 5;
	i = (int)map->player.pos.y - 5;
	while (i < map->height && i - y < (int)map->player.pos.y + 5)
	{
		while (j < map->width && j - x < (int)map->player.pos.x + 5)
		{
			draw_rect(map, i - y, j - x);
			j++;
		}
		i++;
	}
	draw_player(map);
}
