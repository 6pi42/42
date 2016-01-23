/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 11:50:10 by cboyer            #+#    #+#             */
/*   Updated: 2016/01/23 16:16:18 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	key_hook(int keycode, t_map *map)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(map->e.mlx, map->e.win);
		exit(0);
	}
	if (keycode == 126)
	{
		map->zoom += 1;
		draw(map);
	}
	if (keycode == 127)
	{
		map->zoom -= 1;
		draw(map);
	}
	return (1);
}

static int	motion_notify(int x, int y, t_map *map)
{
	if (x < WIDTH && y < HEIGHT && x >= 0 && y >= 0)
	{
		map->julia.i = 1.5 * (y - WIDTH / 2) / (0.5 * map->zoom * WIDTH);
		map->julia.r = 1.5 * (x - HEIGHT / 2) / (0.5 * map->zoom * HEIGHT);
		draw(map);
	}
	return (0);
}

static int	expose_hook(t_map *map)
{
	draw(map);
	return (1);
}

void	draw(t_map *map)
{
	if (!(map->img.img = mlx_new_image(map->e.mlx, WIDTH, HEIGHT)))
		ft_error();
	map->img.data = mlx_get_data_addr(map->img.img, &(map->img.bpp),
			&(map->img.size_line), &(map->img.endian));
	init_img(map, 0x000000);
	if (!ft_strcmp(map->mode, "mandelbrot"))
		mandelbrot(map, 120);
	else if (!ft_strcmp(map->mode, "julia"))
		julia(map, 120);
	//else if (ft_strcmp(mode, ""))
	//else
	//	ft_error();
	mlx_put_image_to_window(map->e.mlx, map->e.win, map->img.img, 0, 0);
	mlx_destroy_image(map->e.mlx, map->img.img);
}

int			main(int argc, const char *argv[])
{
	t_map	*map;
	t_env	e;

	map = (t_map*)malloc(sizeof(t_map));
	if (!(e.mlx = mlx_init()))
		ft_error();
	if (!(e.win = mlx_new_window(e.mlx, WIDTH, HEIGHT, "fractol")))
		ft_error();
	if (argc != 2)
		ft_error();
	else
	{
		map->mode = ft_strdup(argv[1]);
		map->e = e;
		map->zoom = 1;
		mlx_key_hook(map->e.win, key_hook, map);
		mlx_expose_hook(map->e.win, expose_hook, map);
		mlx_hook(e.win, 6, (1L<<6), motion_notify, map);
		mlx_loop(e.mlx);
	}
	return (0);
}
