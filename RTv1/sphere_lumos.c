/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_lumos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 13:31:54 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/24 13:32:52 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec	get_normal_sphere(t_sphere *sphere, t_vec ray, t_map *map)
{
	t_vec norm;

	norm.x = (map->tab->cam.pos.x + ray.x * sphere->t) - sphere->pos.x;
	norm.y = (map->tab->cam.pos.y + ray.y * sphere->t) - sphere->pos.y;
	norm.z = (map->tab->cam.pos.z + ray.z * sphere->t) - sphere->pos.z;
	normalize_vec(&norm);
	return (norm);
}

int		sphere_lumos_diff(t_map *map, void *obj, t_vec inter, int rgb)
{
	t_vec		light;
	double		angle;
	t_sphere	*sphere;
	t_vec		org;

	org = *map->tab->spot_a;
	sphere = (t_sphere*)obj;
	light = sous_vec(inter, org);
	angle = fmax(dot_vec(light, sphere->norm), 0.0);
	rgb = light_rgb(rgb, angle);
	return (rgb);
}
int		sphere_lumos_spec(t_map *map, void *ob, t_vec inter, int rgb)
{
	t_vec		light;
	t_vec		half;
	double		tmp;
	t_sphere	*sphere;
	t_vec		eye;

	sphere = (t_sphere*)ob;
	eye = sous_vec(inter, map->tab->cam.pos);
	light = sous_vec(inter, *map->tab->spot_a);
	if (dot_vec(light, sphere->norm) > 0.0)
	{
		half.x = light.x + eye.x;
		half.y = light.y + eye.y;
		half.z = light.z + eye.z;
		normalize_vec(&half);
		tmp = fmax(0.0, dot_vec(half, sphere->norm));
		tmp = pow(tmp, 16.0);
		return (specular(rgb, 0xFFFFFF, tmp));
	}
	return (rgb);
}
