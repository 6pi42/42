/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 16:45:29 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/23 16:27:29 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	expose_hook(t_map *map)
{
	if (!(map->img.img =
		mlx_new_image(map->e.mlx, map->tab->screen.x, map->tab->screen.y)))
		ft_error();
	map->img.data = mlx_get_data_addr(map->img.img, &(map->img.bpp),
	&(map->img.size_line), &(map->img.endian));
	multi_threading(map, &raytracer);
	mlx_put_image_to_window(map->e.mlx, map->e.win, map->img.img, 0, 0);
	mlx_destroy_image(map->e.mlx, map->img.img);
	return (1);
}
