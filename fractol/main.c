/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 11:50:10 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/11 15:32:06 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		init_key(t_map *map)
{
	map->key.right = 0;
	map->key.left = 0;
	map->key.backward = 0;
	map->key.forward = 0;
	map->max_iter = 100;
	map->zoom = 1;
	map->mouse.y = HEIGHT;
	map->mouse.x = WIDTH;
	map->c = 0;
}

static int	loop_hook(t_map *map)
{
	if (map->key.right == 1)
	{
		map->mouse.x += 100;
		draw(map);
	}
	if (map->key.left == 1)
	{
		map->mouse.x -= 100;
		draw(map);
	}
	if (map->key.backward == 1)
	{
		map->mouse.y += 100;
		draw(map);
	}
	if (map->key.forward == 1)
	{
		map->mouse.y -= 100;
		draw(map);
	}
	return (1);
}

int			main(int argc, const char *argv[])
{
	t_map	*map;

	if (argc != 2 || (ft_strcmp(argv[1], "julia") && ft_strcmp(argv[1],
			"mandelbrot") && ft_strcmp(argv[1], "burning_ship") &&
				ft_strcmp(argv[1], "rabbit") && ft_strcmp(argv[1], "siegel")))
		ft_print_choices();
	if (!(map = (t_map*)malloc(sizeof(t_map))))
		return (0);
	map->mode = ft_strdup(argv[1]);
	if (!(map->e.mlx = mlx_init()))
		ft_error();
	if (!(map->e.win = mlx_new_window(map->e.mlx, WIDTH, HEIGHT, "fractol")))
		ft_error();
	init_key(map);
	mlx_key_hook(map->e.win, key_hook, map);
	mlx_expose_hook(map->e.win, expose_hook, map);
	mlx_loop_hook(map->e.mlx, loop_hook, map);
	mlx_hook(map->e.win, 2, (1L << 0), key_press, map);
	mlx_hook(map->e.win, 6, (1L << 6), motion_notify, map);
	mlx_mouse_hook(map->e.win, buttonpress_hook, map);
	mlx_loop(map->e.mlx);
	return (0);
}
