/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 16:47:16 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/28 14:17:09 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec	init_ray(t_map *map, int x, int y)
{
	t_vec	ray;

	ray.x = (x - map->tab->screen.x / 2) * 1;
	ray.y = (y - map->tab->screen.y / 2) * 1;
	ray.z = -(map->tab->screen.x / (2 * tan((90 / 2) * M_PI / 180.0)));
	return (ray);
}

int		smaller_void(void **st)
{
	int		i;
	double	tmp;
	int		j;

	i = 0;
	tmp = -1;
	j = -1;
	while (i < NB_OBJ)
	{
		if (st[i] != NULL && ((tmp == -1 && (*(double*)st[i] != -1))
			|| (tmp > (*(double*)st[i]))))
		{
			tmp = *(double*)st[i];
			j = i;
		}
		i++;
	}
	if (j == -1)
		return (-1);
	return (*(int*)(st[j] + sizeof(double)));
}

void	reset(void **st, int rgb)
{
	int	i;

	i = 0;
	while (i < NB_OBJ)
	{
		st[i] = NULL;
		i++;
	}
	rgb = -1;
}

void	raytracer(t_map *map)
{
	int		y;
	int		x;
	void	*st[NB_OBJ];
	int		rgb;

	y = 0;
	while (y < map->tab->screen.y)
	{
		x = 0;
		while (x < map->tab->screen.x)
		{
			if (map->tab->nb_sphere > 0)
				st[0] = nearest_sphere(y, x, map, map->tab->sphere);
			st[1] = plan(map, x, y);
			if ((rgb = smaller_void(st)) != -1)
				pixel_put(map, x, y, rgb);
			reset(st, rgb);
			x++;
		}
		y++;
	}
}
