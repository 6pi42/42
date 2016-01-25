/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/23 15:51:24 by cboyer            #+#    #+#             */
/*   Updated: 2016/01/24 15:03:12 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		ft_error(void)
{
	ft_putstr("error\n");
	exit(0);
}

void		ft_print_choices(void)
{
	ft_putstr("-mandelbrot\n-julia\n-sierpinski\n-burning_ship\n");
	exit(0);
}

void	draw(t_map *map)
{
	if (!(map->img.img = mlx_new_image(map->e.mlx, WIDTH, HEIGHT)))
		ft_error();
	map->img.data = mlx_get_data_addr(map->img.img, &(map->img.bpp),
			&(map->img.size_line), &(map->img.endian));
	init_img(map, 0x000000);
	if (!ft_strcmp(map->mode, "mandelbrot"))
		mandelbrot(map);
	else if (!ft_strcmp(map->mode, "julia"))
		julia(map);
	else if (!ft_strcmp(map->mode, "sierpinski"))
		sierpinski(map);
	else if (!ft_strcmp(map->mode, "burning_ship"))
		burning_ship(map);
	else
		ft_print_choices();
	mlx_put_image_to_window(map->e.mlx, map->e.win, map->img.img, 0, 0);
	mlx_destroy_image(map->e.mlx, map->img.img);
}
