/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 11:50:10 by cboyer            #+#    #+#             */
/*   Updated: 2016/01/14 15:07:37 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_error(void)
{
	ft_putstr("error\n");
	exit(0);
}

static int	key_hook(int keycode, t_env *e)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(e->mlx, e->win);
		exit(0);
	}
	return (1);
}

static int	expose_hook(t_map *map)
{
	if (!(map->img.img = mlx_new_image(map->e.mlx, WIDTH, HEIGHT)))
		ft_error();
	map->img.data = mlx_get_data_addr(map->img.img, &(map->img.bpp),
			&(map->img.size_line), &(map->img.endian));
	init_img(map, 0x000000);
	draw(map);
	mlx_put_image_to_window(map->e.mlx, map->e.win, map->img.img, 0, 0);
	mlx_destroy_image(map->e.mlx, map->img.img);
	return (1);
}

int			main(int argc, const char *argv[])
{
	t_map	*map;
	t_env	e;

	map = NULL;
	if (!(e.mlx = mlx_init()))
		ft_error();
	if (!(e.win = mlx_new_window(e.mlx, WIDTH, HEIGHT, "fdf")))
		ft_error();
	if (argc != 2)
		ft_error();
	else
	{
		map = ft_parse((char *)argv[1]);
		map->e = e;
		mlx_expose_hook(map->e.win, expose_hook, map);
		mlx_key_hook(map->e.win, key_hook, &map->e);
		mlx_loop(e.mlx);
	}
	return (0);
}
