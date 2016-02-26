/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Client <Client@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 16:47:16 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/26 17:59:29 by Client           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec    init_ray(t_map *map, int x, int y)
{
	t_vec   ray;
	ray.x = (x - map->tab->screen.x / 2) * 1;
	ray.y = (y - map->tab->screen.y / 2) * 1;
	ray.z = -(map->tab->screen.x / (2 * tan((90 / 2) * M_PI / 180.0)));
	return (ray);
}

double	init_inter(t_sphere s, int i, int j, t_map *map, int *valid)
{
	double		a;
	double		b;
	double		c;
	double		t;
	double		d;
	double		tmp;
	t_vec		ray;
	t_cam		cam;

	cam = map->tab->cam;
	ray = init_ray(map, j, i);
	a = ray.x * ray.x + ray.y * ray.y + ray.z * ray.z;
	b =  2 * (ray.x * (cam.pos.x - s.pos.x)
			+ ray.y * (cam.pos.y - s.pos.y)
			+ ray.z * (cam.pos.z - s.pos.z));
	c = (cam.pos.x - s.pos.x) * (cam.pos.x - s.pos.x)
	  + (cam.pos.y - s.pos.y) * (cam.pos.y - s.pos.y)
	  + (cam.pos.z - s.pos.z) * (cam.pos.z - s.pos.z)
		- s.radius * s.radius;
	d = (b * b) - (4 * a * c);
	if (d == 0)
	{
		t = (-1 * b + sqrt(d)) / (2 * a);
		*valid = 1;
	}
	else if (d > 0)
	{
		t = (-1 * b - sqrt(d)) / (2 * a);
		tmp = (-1 * b + sqrt(d)) / (2 * a);
		t = t < tmp ? t : tmp;
		*valid = 1;
	}
	else
		return (0);
	return (t);
}

int		get_smaller(double *t, int c, int *valid)
{
	int i;
	int j;
	double	tmp;

	tmp = t[0];
	j = -1;
	i = 0;
	while (i < c)
	{
		if (valid[i] && t[i] < tmp)
		{
			tmp = t[i];
			j = i;
		}
		i++;
	}
	return (j);
}

void nearest(int y, int x, t_map *map)
{
	int		i;
	double t[map->tab->nb_sphere];
	int		small;
	int		*valid;

	valid = (int*)malloc(sizeof(int) * map->tab->nb_sphere);
	i = 0;
	while (i < map->tab->nb_sphere)
	{
		valid[i] = 0;
		i++;
	}
	i = 0;
	while (i < map->tab->nb_sphere)
	{
		t[i] = init_inter(map->tab->sphere[i], y, x, map, &valid[i]);
		i++;
	}
	small = get_smaller(t, map->tab->nb_sphere, valid);
	if (small != -1)
		pixel_put(map, x, y, map->tab->sphere[small].rgb);
}

void	raytracer(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	while (i < map->tab->screen.y)
	{
		j = 0;
		while (j < map->tab->screen.x)
		{
			nearest(i, j, map);
			j++;
		}
		i++;
	}
}
