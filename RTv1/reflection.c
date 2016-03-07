/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 14:02:22 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/07 15:00:15 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


t_vec	inter_point(t_vec ray, void* obj, t_vec org)
{
	t_vec	pos;

	pos.x = org.x * *(double*)obj - ray.x;
	pos.y = org.y * *(double*)obj - ray.y;
	pos.z = org.z * *(double*)obj - ray.z;
	return (pos);
}

t_vec	get_refl_ray(t_vec norm, t_vec ray)
{
	t_vec	r;

	r = sous_vec(mult_int_vec(mult_int_vec(norm, dot_vec(norm, ray)), 2.0),
		ray);
	return (r);
}

int		sphere_reflexion(t_map *map, t_sphere *sphere, t_vec ray, int rgb)
{
	t_vec	refl;
	t_vec	norm;
	void	*st[NB_OBJ];
	t_vec	pos;
	void	*small;

	pos = inter_point(ray, (void*)sphere, map->tab->cam.pos);
	norm = get_normal_sphere(sphere, ray, map);
	refl = get_refl_ray(norm, ray);
	st[0] = nearest_sphere(refl, map, map->tab->sphere, pos);
	st[1] = nearest_plan(map->tab->spot, refl, map);
	st[2] = nearest_cyl(refl, map, map->tab->cylinder, pos);
	//st[3] = nearest_cone(light, map, map->tab->cone, map->tab->spot);
	st[3] = NULL;
	small = smaller_void(st);
	if (small != NULL)
		return (rgb);
		//rgb = compo(rgb, *(int*)(small + sizeof(double)));
	return (rgb);
}
