/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 16:36:48 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/23 16:26:23 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	main(int argc, char **argv)
{
	t_env	e;
	t_map	*map;

	if (argc != 2)
		ft_error_arg();
	if (!(e.mlx = mlx_init()))
		ft_error_mlx();
	if (!(map = (t_map*)malloc(sizeof(t_map))))
		ft_error_malloc();
	map->tab = parse(argv[1]);
	return (1);
	if (map->tab->screen.x <= 0 || map->tab->screen.y <= 0)
		ft_error_file();
	if (!(e.win =
		mlx_new_window(e.mlx, map->tab->screen.x, map->tab->screen.y, "Rtv1")))
		ft_error_mlx();
	mlx_expose_hook(map->e.win, expose_hook, map);
	mlx_loop(e.mlx);
	return (0);
}
