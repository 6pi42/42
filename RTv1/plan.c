/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 19:55:28 by Client            #+#    #+#             */
/*   Updated: 2016/03/16 12:52:19 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	get_inter_plan(t_plan *plan, t_vec ray, t_vec org)
{
	double	t;
	t_vec	nor;
	t_vec	pt;

	nor = plan->norm;
	pt = plan->pos;
	t = -(((nor.x * (org.x - pt.x)) +
			(nor.y * (org.y - pt.y)) +
			(nor.z * (org.z - pt.z)))
			/ ((nor.x * ray.x) + (nor.y * ray.y) + (nor.z * ray.z)));
	plan->t = t < 0.0 ? -1 : t;

}


int		get_smaller_plan(t_plan *plan, int c)
{
	int		i;
	int		j;
	double	tmp;

	if (c >= 1)
		tmp = plan[0].t;
	else
		return (-1);
	j = 0;
	i = 0;
	while (i < c)
	{
		if (tmp <= 0 || (tmp > plan[i].t && plan[i].t > 0))
		{
			tmp = plan[i].t;
			j = i;
		}
		i++;
	}
	j = tmp == -1 ? -1 : j;
	return (j);
}



void	*nearest_plan(t_vec org, t_vec ray, t_map *map)
{
	int	i;
	int	small;

	i = 0;
	while (i < map->tab->nb_plan)
	{
		get_inter_plan(&map->tab->plan[i], ray, org);
		i++;
	}
	small = get_smaller_plan(map->tab->plan, map->tab->nb_plan);
	if (small == -1)
		return (NULL);
	return ((void*)&map->tab->plan[small]);
}

int		plan_lumos(t_map *map, t_plan *plan, t_vec ray)
{
	int		rgb;
	t_vec	light;
	double	angle;
	t_vec	norm;
	t_vec	inter;

	inter = intersection(plan, ray, map->tab->cam.pos);
	light = sous_vec(map->tab->spot, inter);
	norm = plan->pos;
	angle = acos(dot_vec(light, norm));
	if (angle <= 0)
		rgb = 0x000000;
	else
		rgb = light_rgb(plan->rgb, angle * 0.6);
	return (rgb);
}
