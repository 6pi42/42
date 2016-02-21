/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 13:30:03 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/21 13:36:05 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	free_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		free(map->map[i]);
		i++;
	}
	free(map->map);
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 64)
		{
			free(map->tex[i][j]);
			j++;
		}
		free(map->tex[i]);
		i++;
	}
	exit(0);
}
