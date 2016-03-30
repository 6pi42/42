/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 16:45:29 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/30 16:21:42 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	free_all(t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->tab->nb_cone)
		free(&(map->tab->cone[i]));
	i = -1;
	while (++i < map->tab->nb_sphere)
		free(&(map->tab->sphere[i]));
	i = -1;
	while (++i < map->tab->nb_cylinder)
		free(&(map->tab->cylinder[i]));
	i = -1;
	while (++i < map->tab->nb_spot)
		free(&(map->tab->spot[i]));
	free(map->tab);
	free(map);
}

int		expose_hook(t_map *map)
{
	if (!(map->img.img =
		mlx_new_image(map->e.mlx, map->tab->screen.x, map->tab->screen.y)))
		ft_error();
	map->img.data = mlx_get_data_addr(map->img.img, &(map->img.bpp),
	&(map->img.size_line), &(map->img.endian));
	raytracer(map);
	mlx_put_image_to_window(map->e.mlx, map->e.win, map->img.img, 0, 0);
	mlx_destroy_image(map->e.mlx, map->img.img);
	return (1);
}

int		key_hook(int keycode, t_map *map)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(map->e.mlx, map->e.win);
		free_all(map);
		exit(0);
	}
	return (1);
}

int		red_cross(t_map *map)
{
	mlx_destroy_window(map->e.mlx, map->e.win);
	free_all(map);
	exit(0);
	return (1);
}
