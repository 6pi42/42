/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 11:26:30 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/20 12:07:25 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_error(void)
{
	ft_putstr("error");
	exit(0);
}

int				get_hex_color(t_map *map, int x, int y)
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;

	red = map->img.data[y * map->img.size_line + (x * map->img.bpp) / 8];
	green = map->img.data[y * map->img.size_line + (x * map->img.bpp) / 8 + 1];
	blue = map->img.data[y * map->img.size_line + (x * map->img.bpp) / 8 + 2];
	return (red << 16 | green << 8 | blue);
}

static	void	free_arg(t_args *arg1, t_args *arg2, t_args *arg3, t_args *arg4)
{
	free(arg1);
	free(arg2);
	free(arg3);
	free(arg4);
}

static t_args	*init_arg(t_map *map, int min, int max)
{
	t_args *arg;

	arg = (t_args*)malloc(sizeof(t_args));
	arg->map = map;
	arg->min = min;
	arg->max = max;
	return (arg);
}

void			multi_threading(t_map *map, void *f)
{
	pthread_t	thread[4];
	t_args		*arg1;
	t_args		*arg2;
	t_args		*arg3;
	t_args		*arg4;

	arg1 = init_arg(map, 0, WIDTH / 4);
	arg2 = init_arg(map, WIDTH / 4, WIDTH / 2);
	arg3 = init_arg(map, WIDTH / 2, 3 * (WIDTH / 4));
	arg4 = init_arg(map, 3 * (WIDTH / 4), WIDTH);
	pthread_create(&thread[0], NULL, f, (void*)arg1);
	pthread_create(&thread[1], NULL, f, (void*)arg2);
	pthread_create(&thread[2], NULL, f, (void*)arg3);
	pthread_create(&thread[3], NULL, f, (void*)arg4);
	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
	pthread_join(thread[2], NULL);
	pthread_join(thread[3], NULL);
	free_arg(arg1, arg2, arg3, arg4);
}
