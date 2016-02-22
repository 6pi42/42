/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 16:36:48 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/22 18:28:08 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	main(int argc, char **argv)
{
	t_env	e;
	t_map	*map;

	if (argc != 2)
		ft_error();
	if (!(e.mlx = mlx_init()))
		ft_error_mlx();
	parse(argv[1]);
	if (map->screen.x <= 0 || map->scree.y <= 0)
		ft_error_file();
	if (!(e.win = mlx_new_window(e.mlx, map->screen.x, map->screen.y, "Rtv1")))
		ft_error_mlx();
	mlx_expose_hook(map->e.win, expose_hook, map);
	mlx_loop(e.mlx);
	return (0);
}
