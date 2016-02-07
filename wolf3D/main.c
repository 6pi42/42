/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 16:07:16 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/07 13:44:04 by cboyer           ###   ########.fr       */
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

void		draw(t_map *map)
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

static void	init_map(t_map *map)
{
	map->player.pos.x = 3.0;
	map->player.pos.y = 3.0;
	map->player.dir.x = -1.0;
	map->player.dir.y = 0.0;
	map->plane.x = 0.0;
	map->plane.y = 0.66;
	map->key.right = 0;
	map->key.left = 0;
	map->key.forward = 0;
	map->key.behind = 0;
	map->key.turn_left = 0;
	map->key.turn_right = 0;
}

static int	loop_hook(t_map *map)
{
	move(map);
	return (0);
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
		init_map(map);
		map->e = e;
		mlx_hook(e.win, 2, (1L << 0), key_press, map);
		mlx_key_hook(map->e.win, key_hook, map);
		mlx_expose_hook(map->e.win, expose_hook, map);
		mlx_loop_hook(e.mlx, loop_hook, map);
		mlx_loop(e.mlx);
	}
	return (0);
}
