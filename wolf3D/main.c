/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 16:07:16 by cboyer            #+#    #+#             */
/*   Updated: 2016/01/26 13:12:14 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

#   include <stdio.h>

void		print_grid(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			printf(" %d ", map->map[i][j].z);
			j++;
		}
		printf("\n");
		i++;
	}
}

int			main(int argc, const char *argv[])
{
	t_map	*map;
	t_env	e;

	if (!(e.mlx = mlx_init()))
		ft_error();
	if (!(e.win = mlx_new_window(e.mlx, WIDTH, HEIGHT, "wolf3D")))
		ft_error();
	if (argc != 2)
		ft_error();
	else
	{
		map = ft_parse((char*)argv[1]);
		print_grid(map);
		map->e = e;
		//mlx_key_hook(map->e.win, key_hook, map);
		mlx_expose_hook(map->e.win, expose_hook, map);
		//mlx_hook(e.win, 6, (1L<<6), motion_notify, map);
		mlx_loop(e.mlx);
	}
	return (0);
}
