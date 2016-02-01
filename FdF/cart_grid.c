/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cart_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 12:05:02 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/01 22:53:26 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	malloc_cart(t_map *map)
{
	int	i;

	i = 0;
	if (!(map->cart = malloc(sizeof(t_point*) * map->height)))
		ft_error();
	while (i < map->height)
	{
		if (!(map->cart[i] = malloc(sizeof(t_point) * map->width)))
			ft_error();
		i++;
	}
}

void		copy_cart(t_map *map)
{
	int	i;
	int	j;

	malloc_cart(map);
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			map->cart[i][j] = map->map[i][j];
			j++;
		}
		i++;
	}
}
