/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 13:27:52 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/07 14:59:47 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	normalize_vec(t_vec *vec)
{
	double tmp;

	tmp = 1.0 / length_vec(*vec);
	vec->x *= tmp;
	vec->y *= tmp;
	vec->z *= tmp;
}

double	length_vec(t_vec vec)
{
	double	length;

	length = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	return (length);
}

double	dot_vec(t_vec a, t_vec b)
{
	double	angle;

	angle = a.x * b.x + a.y * b.y + a.z * b.z;
	return (angle);
}

t_vec	cross_product_vec(t_vec a, t_vec b)
{
	t_vec	cross;

	cross.x = a.y * b.z - b.y * a.z;
	cross.y = a.z * b.x - b.z * a.x;
	cross.x = a.x * b.y - b.x * a.y;
	return (cross);
}

t_vec	mult_int_vec(t_vec a, double i)
{
	t_vec b;

	b.x = a.x * i;
	b.y = a.y * i;
	b.z = a.z * i;
	return (b);
}

t_vec	sous_vec(t_vec a, t_vec b)
{
	t_vec	c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - c.z;
	return (c);
}
