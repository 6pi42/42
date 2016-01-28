/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 11:50:10 by cboyer            #+#    #+#             */
/*   Updated: 2016/01/27 11:50:36 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			main(int argc, const char *argv[])
{
	t_map	*map;

	map = (t_map*)malloc(sizeof(t_map));
	map->mode = ft_strdup(argv[1]);
	if (argc != 2 || (ft_strcmp(map->mode, "julia") && ft_strcmp(map->mode,
					"mandelbrot") && ft_strcmp(map->mode, "burning_ship")))
		ft_print_choices();
	if (!(map->e.mlx = mlx_init()))
		ft_error();
	if (!(map->e.win = mlx_new_window(map->e.mlx, WIDTH, HEIGHT, "fractol")))
		ft_error();
	map->zoom = 1;
	map->mouse.y = HEIGHT;
	map->mouse.x = WIDTH;
	map->max_iter = 100;
	mlx_key_hook(map->e.win, key_hook, map);
	mlx_expose_hook(map->e.win, expose_hook, map);
	mlx_hook(map->e.win, 6, (1L << 6), motion_notify, map);
	//mlx_hook(e.win, 6, (1L<<11), circulate_notify_down, map);
	//mlx_hook(e.win, 6, (1L<<12), circulate_notify_up, map);
	mlx_loop(map->e.mlx);
	return (0);
}
