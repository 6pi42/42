/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_lumos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 13:31:54 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/09 13:04:15 by cboyer           ###   ########.fr       */
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



int		sphere_lumos_diff(t_map *map, t_sphere *sphere, t_vec ray)
{
	int		rgb;
	t_vec	light;
	double	angle;
	t_vec	norm;

	light = get_light_ray((void*)sphere, ray, map, map->tab->spot);
	norm = get_normal_sphere(sphere, ray, map);
	angle = acos(dot_vec(light, norm));
	if (angle <= 0)
		rgb = 0x000000;
	else
		rgb = light_rgb(sphere->rgb, angle * 0.6);
	return (rgb);
}

int		sphere_lumos_spec(t_map *map, t_sphere *sphere, t_vec ray, int diffuse)
{
	t_vec	norm;
	double	refl;
	double	coef;
	int		rgb;
	t_vec	light;
	double	costheta;
	t_vec	vector;
	t_vec	tmp;
	t_vec	reflectvec;
	int		spec;

	light = get_light_ray((void*)sphere, ray, map, map->tab->spot);
	norm = get_normal_sphere(sphere, norm, map);
	costheta = dot_vec(light, norm);
	costheta = costheta < 0.0 ? 0.0 : costheta;
	rgb = light_rgb(diffuse, costheta);
	vector = sous_vec(norm, light);
	refl = 2.0 * -(dot_vec(norm, light));
	tmp = mult_int_vec(norm, refl);
	reflectvec = add_vec(tmp, norm);
	coef = fmax(-dot_vec(reflectvec, norm), 0);
	coef = powf(coef, 5);
	spec = light_rgb(sphere->rgb ,coef);
	rgb =  add_rgb(rgb, spec);
	return (rgb);

}

int	sphere_lumos(t_map *map, t_sphere *sphere, t_vec ray)
{
	int	diffuse;
	int	spec;

	diffuse = sphere_lumos_diff(map, sphere, ray);
	//spec = sphere_lumos_spec(map, sphere, ray, diffuse);
	spec = diffuse;
	return (spec);
}
