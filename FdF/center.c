/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 10:48:03 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/03 13:48:04 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_map	*div_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			map->map[i][j].x /= 2;
			map->map[i][j].y /= 2;
			j++;
		}
		i++;
	}
	return (map);
}

static t_map	*get_offset(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width && i != -1)
		{
			if (map->map[i][j].x + (WIDTH / 2) >= WIDTH
					|| map->map[i][j].y + (HEIGHT / 2) >= HEIGHT
					|| map->map[i][j].x + (WIDTH / 2) < 0
					|| map->map[i][j].y + (HEIGHT / 2) < 0)
			{
				map = div_map(map);
				i = -1;
				j = 0;
			}
			else
				j++;
		}
		i++;
	}
	return (map);
}

static void		get_z_offset(t_map *map)
{
	int	zmin;
	int	zmax;
	int	i;
	int	j;
	int	rst;

	i = 0;
	zmin = 0;
	zmax = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			zmin = map->map[i][j].z < zmin ? map->map[i][j].z : zmin;
			zmax = map->map[i][j].z > zmax ? map->map[i][j].z : zmax;
			j++;
		}
		i++;
	}
	rst = 42 - abs(zmax - zmin);
	map->z_offset = rst <= 0 ? 10 : rst;
}

static void		get_z(t_map *map, int i, int j)
{
	if (fmod(map->angle, 180) == 90.0)
	{
		map->map[i][j].x -= map->map[i][j].z * map->z_offset;
		map->map[i][j].y -= map->map[i][j].z * map->z_offset;
	}
	else
	{
		map->map[i][j].y += map->map[i][j].z * map->z_offset;
		map->map[i][j].x += map->map[i][j].z * map->z_offset;
	}
}

t_map			*center(t_map *map)
{
	int		i;
	int		j;
	int		tmp;

	i = -1;
	get_z_offset(map);
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			map->map[i][j].x = map->cart[i][j].x;
			map->map[i][j].y = map->cart[i][j].y;
			map->map[i][j].x -= (map->width / 2);
			map->map[i][j].y -= (map->height / 2);
			map->map[i][j].x *= WIDTH / 10;
			map->map[i][j].y *= WIDTH / 10;
			get_z(map, i, j);
			tmp = map->map[i][j].x;
			map->map[i][j].x = tmp - map->map[i][j].y;
			map->map[i][j].y = (tmp + map->map[i][j].y) / 2;
		}
	}
	map = get_offset(map);
	return (map);
}
