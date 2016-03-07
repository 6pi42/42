/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 19:55:28 by Client            #+#    #+#             */
/*   Updated: 2016/03/07 13:36:15 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec	get_norm_plan(t_plan *plan, t_vec ray, t_map *map)
{
	t_vec norm;

	(void)plan;
	(void)ray;
	(void)map;
	norm.x = 0.0;
	norm.y = 1.0;
	norm.z = 0.0;
	return (norm);
}

void	get_inter_plan(t_plan *plan, t_vec ray, t_map *map, t_vec org)
{
	double	t;
	t_vec	nor;

	nor = get_norm_plan(plan, ray, map);
	t = -(((nor.x * (org.x - 0.0)) +
			(nor.y * (org.y - 0.0)) +
			(nor.z * (org.z - 0.0)))
			/ ((nor.x * ray.x) + (nor.y * ray.y) + (nor.z * ray.z)));
	plan->t = t <= 0 ? -1 : t;

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
	t_plan	*plan;

	plan = map->tab->plan;
	i = 0;
	while (i < map->tab->nb_plan)
	{
		get_inter_plan(&plan[i], ray, map, org);
		i++;
	}
	small = get_smaller_plan(plan, map->tab->nb_plan);
	if (small == -1)
		return (NULL);
	return ((void*)&plan[small]);
}

int		plan_lumos(t_map *map, t_plan *plan, t_vec ray)
{
	int		rgb;
	t_vec	light;
	double	angle;
	t_vec	norm;

	light = get_light_ray((void*)plan, ray, map);
	norm = get_norm_plan(plan, ray, map);
	angle = acos(dot_vec(light, norm));
	if (angle <= 0)
		rgb = 0x000000;
	else
		rgb = light_rgb(plan->rgb, angle * 0.6);
	return (rgb);
}
