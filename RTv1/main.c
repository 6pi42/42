/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 16:36:48 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/28 14:03:35 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	print_object(t_tab *tab)
{
	int i;

	printf("screen: %d %d\n\n", tab->screen.x, tab->screen.y);
	printf("cam pos: x %f y %f z %f\n", tab->cam.pos.x,
		tab->cam.pos.y, tab->cam.pos.z);
	printf("cam rotate: x %f y %f z %f\n\n", tab->cam.rotate.x,
		tab->cam.rotate.y, tab->cam.rotate.z);
	printf("plan pos: x %f y %f z %f\n", tab->plan.pos.x,
		tab->plan.pos.y, tab->plan.pos.z);
	printf("plan: rgb %#x\n\n", tab->plan.rgb);
	i = 0;
	while (i < tab->nb_sphere)
	{
		printf("sphere[%d]\n\n", i);
		printf("rayon: %f\n", tab->sphere[i].radius);
		printf("pos: x %f y %f z %f\n", tab->sphere[i].pos.x,
		tab->sphere[i].pos.y, tab->sphere[i].pos.z);
		printf("rgb: %#x\n\n", tab->sphere[i].rgb);
		i++;
	}
	i = 0;
	while (i < tab->nb_cone)
	{
		printf("cone[%d]\n\n", i);
		printf("rayon: %f\n", tab->cone[i].radius);
		printf("pos: x %f y %f z %f\n", tab->cone[i].pos.x,
		tab->cone[i].pos.y, tab->cone[i].pos.z);
		printf("rgb: %d\n", tab->cone[i].rgb);
		printf("height: %f\n\n", tab->cone[i].height);
		i++;
	}
	i = 0;
	while (i < tab->nb_cylinder)
	{
		printf("cylinder[%d]\n\n", i);
		printf("rayon: %f\n", tab->cylinder[i].radius);
		printf("pos: x %f y %f z %f\n", tab->cylinder[i].pos.x,
		tab->cylinder[i].pos.y, tab->cylinder[i].pos.z);
		printf("rgb: %d\n", tab->cylinder[i].rgb);
		printf("height: %f\n\n", tab->cylinder[i].height);
		i++;
	}
}

void	print_tab(t_tab *tab)
{
	print_object(tab);
}

int		main(int argc, char **argv)
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
	print_tab(map->tab);
	if (map->tab->screen.x <= 0 || map->tab->screen.y <= 0)
		ft_error_file();
	if (!(e.win =
		mlx_new_window(e.mlx, map->tab->screen.x, map->tab->screen.y, "Rtv1")))
		ft_error_mlx();
	map->e = e;
	mlx_expose_hook(map->e.win, expose_hook, map);
	mlx_key_hook(map->e.win, key_hook, map);
	mlx_loop(e.mlx);
	return (0);
}
