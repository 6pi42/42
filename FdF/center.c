/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 10:48:03 by cboyer            #+#    #+#             */
/*   Updated: 2016/01/14 15:05:24 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	t_map	*div_map(t_map *map)
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

static	t_map	*get_offset(t_map *map)
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

t_map			*center(t_map *map)
{
	int		i;
	int		j;
	int		tmp;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			map->map[i][j].x -= (map->width / 2);
			map->map[i][j].y -= (map->height / 2);
			map->map[i][j].x -= map->map[i][j].z;
			map->map[i][j].y -= map->map[i][j].z;
			map->map[i][j].x *= WIDTH;
			map->map[i][j].y *= WIDTH;
			tmp = map->map[i][j].x;
			map->map[i][j].x = tmp - map->map[i][j].y;
			map->map[i][j].y = (tmp + map->map[i][j].y) / 2;
			j++;
		}
		i++;
	}
	map = get_offset(map);
	return (map);
}
