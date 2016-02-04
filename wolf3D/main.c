/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 16:07:16 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/04 18:12:43 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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

void	draw(t_map *map)
{
	if (!(map->img.img = mlx_new_image(map->e.mlx, WIDTH, HEIGHT)))
		ft_error();
	map->img.data = mlx_get_data_addr(map->img.img, &(map->img.bpp),
			&(map->img.size_line), &(map->img.endian));
	init_img(map, 0x000000);
	raycasting(map);
	mlx_put_image_to_window(map->e.mlx, map->e.win, map->img.img, 0, 0);
	mlx_destroy_image(map->e.mlx, map->img.img);
}

int		expose_hook(t_map *map)
{
	draw(map);
	return (1);
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
		map->player.pos.x = 4.0;
		map->player.pos.y = 4.0;
		map->player.dir.x = -1.0;
		map->player.dir.y = 0.0;
		map->plane.x = 0.0;
		map->plane.y = 0.66;
		map->e = e;
		mlx_key_hook(map->e.win, key_hook, map);
		mlx_expose_hook(map->e.win, expose_hook, map);
		//mlx_hook(e.win, 6, (1L<<6), motion_notify, map);
		mlx_loop(e.mlx);
	}
	return (0);
}
