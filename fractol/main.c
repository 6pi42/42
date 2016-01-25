/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 11:50:10 by cboyer            #+#    #+#             */
/*   Updated: 2016/01/24 15:18:46 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
		ft_print_choices();
	else
	{
		map->mode = ft_strdup(argv[1]);
		map->e = e;
		map->zoom = 1;
		map->mouse.y = HEIGHT;
		map->mouse.x = WIDTH;
		mlx_key_hook(map->e.win, key_hook, map);
		mlx_expose_hook(map->e.win, expose_hook, map);
		mlx_hook(e.win, 6, (1L<<6), motion_notify, map);
		//mlx_hook(e.win, 6, (1L<<11), circulate_notify_down, map);
		//mlx_hook(e.win, 6, (1L<<12), circulate_notify_up, map);
		mlx_loop(e.mlx);
	}
	return (0);
}
