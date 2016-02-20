/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 17:03:27 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/20 17:02:03 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	init_pos(t_map *map, t_pos *start, t_pos *end)
{
	int x;
	int y;

	x = (int)floor(map->player.pos.x);
	y = (int)floor(map->player.pos.y);
	start->x = x - 5 > 0 ? x - 5 : 0;
	end->x = x + 5 < map->width ? x + 5 : map->width;
	start->y = y - 5 > 0 ? y - 5 : 0;
	end->y = y + 5 < map->height ? y + 5 : map->height;
}

static void	draw_square(t_map *map, int x, int y, int color)
{
	int i;
	int j;

	i = y + 10;
	j = x + 10;
	while (y < i)
	{
		x = j - 10;
		while (x < j)
		{
			pixel_put_mmap(map, x, y, color);
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

static void	print_map(t_map *map)
{
	int		tmp;
	int		color;
	int		i;
	int		j;
	t_pos	start;
	t_pos	end;

	init_pos(map, &start, &end);
	j = 10 - (end.y - start.y);
	j = end.y == map->width ? 0 : 10 - (end.y - start.y);
	while (start.y < end.y)
	{
		tmp = start.x;
		i = 10 - (end.x - tmp);
		i = end.x == map->height ? 0 : 10 - (end.x - start.x);
		while (tmp < end.x)
		{
			color = map->map[tmp][start.y].z == 0 ? 0x010101 : 0xFF0000;
			if (map->map[tmp][start.y].z != 0)
				draw_square(map, (j * 10) - (fmod(map->player.pos.y, 1) * 10 ),
					(i * 10) - (fmod(map->player.pos.x, 1) * 10), color);
			tmp++;
			i++;
		}
		start.y++;
		j++;
	}
}

void	mini_map(t_map *map)
{
	map->mmap.img = mlx_new_image(map->e.mlx, 100, 100);
	map->mmap.data = mlx_get_data_addr(map->mmap.img, &(map->mmap.bpp),
			&(map->mmap.size_line), &(map->mmap.endian));
	init_mmap(map);
	print_map(map);
	pixel_put_mmap(map, 49, 50, 0x00FF00);
	pixel_put_mmap(map, 51, 50, 0x00FF00);
	pixel_put_mmap(map, 50, 49, 0x00FF00);
	pixel_put_mmap(map, 50, 51, 0x00FF00);
	mlx_put_image_to_window(map->e.mlx, map->e.win, map->mmap.img,
			WIDTH - 125, HEIGHT - 125);
	mlx_destroy_image(map->e.mlx, map->mmap.img);
}
