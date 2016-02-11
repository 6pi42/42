/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/23 15:51:24 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/10 11:42:45 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_error(void)
{
	ft_putstr("error\n");
	exit(0);
}

void	ft_print_choices(void)
{
	ft_putstr("-mandelbrot\n-julia\n-burning_ship\n-rabbit\n-siegel\n");
	exit(0);
}

void	draw(t_map *map)
{
	char *str;
	char *tmp;

	str = ft_itoa_base(map->max_iter, 10);
	tmp = ft_strjoin("Iter:", str);
	free(str);
	if (!(map->img.img = mlx_new_image(map->e.mlx, WIDTH, HEIGHT)))
		ft_error();
	map->img.data = mlx_get_data_addr(map->img.img, &(map->img.bpp),
			&(map->img.size_line), &(map->img.endian));
	init_img(map, 0x000000);
	if (!ft_strcmp(map->mode, "mandelbrot"))
		mandelbrot(map);
	else if (!ft_strcmp(map->mode, "julia"))
		julia(map);
	else if (!ft_strcmp(map->mode, "burning_ship"))
		burning_ship(map);
	else if (!ft_strcmp(map->mode, "rabbit"))
		rabbit(map);
	else if (!ft_strcmp(map->mode, "siegel"))
		siegel(map);
	mlx_put_image_to_window(map->e.mlx, map->e.win, map->img.img, 0, 0);
	mlx_string_put(map->e.mlx, map->e.win, 0, 0, 0x000000, tmp);
	free(tmp);
	mlx_destroy_image(map->e.mlx, map->img.img);
}
