/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_smaller_triangle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/24 12:06:31 by cboyer            #+#    #+#             */
/*   Updated: 2016/01/24 12:14:01 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	get_smaller_1(t_point tmp[3], t_point pt[3])
{
	tmp[0].x = (pt[0].x + pt[1].x) / 2 + (pt[1].x - pt[2].x) / 2;
	tmp[0].y = (pt[0].y + pt[1].y) / 2 + (pt[1].y - pt[2].y) / 2;
	tmp[1].x = (pt[0].x + pt[1].x) / 2 + (pt[0].x - pt[2].x) / 2;
	tmp[1].y = (pt[0].y + pt[1].y) / 2 + (pt[0].y - pt[2].y) / 2;
	tmp[2].x = (pt[0].x + pt[1].x) / 2;
	tmp[2].y = (pt[0].y + pt[1].y) / 2;
}

void	get_smaller_2(t_point tmp[3], t_point pt[3])
{
	tmp[0].x = (pt[2].x + pt[1].x) / 2 + (pt[1].x - pt[0].x) / 2;
	tmp[0].y = (pt[2].y + pt[1].y) / 2 + (pt[1].y - pt[0].y) / 2;
	tmp[1].x = (pt[2].x + pt[1].x) / 2 + (pt[2].x - pt[0].x) / 2;
	tmp[1].y = (pt[2].y + pt[1].y) / 2 + (pt[2].y - pt[0].y) / 2;
	tmp[2].x = (pt[2].x + pt[1].x) / 2;
	tmp[2].y = (pt[2].y + pt[1].y) / 2;
}

void	get_smaller_3(t_point tmp[3], t_point pt[3])
{
	tmp[0].x = (pt[0].x + pt[2].x) / 2 + (pt[2].x - pt[1].x) / 2;
	tmp[0].y = (pt[0].y + pt[2].y) / 2 + (pt[2].y - pt[1].y) / 2;
	tmp[1].x = (pt[0].x + pt[2].x) / 2 + (pt[0].x - pt[1].x) / 2;
	tmp[1].y = (pt[0].y + pt[2].y) / 2 + (pt[0].y - pt[1].y) / 2;
	tmp[2].x = (pt[0].x + pt[2].x) / 2;
	tmp[2].y = (pt[0].y + pt[2].y) / 2;
}

