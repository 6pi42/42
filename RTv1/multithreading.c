/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 13:18:54 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/23 16:27:57 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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

	arg1 = init_arg(map, 0, map->tab->screen.x / 4);
	arg2 = init_arg(map, map->tab->screen.x / 4, map->tab->screen.x / 2);
	arg3 = init_arg(map, map->tab->screen.x / 2, 3 * (map->tab->screen.x / 4));
	arg4 = init_arg(map, 3 * (map->tab->screen.x / 4), map->tab->screen.x);
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
