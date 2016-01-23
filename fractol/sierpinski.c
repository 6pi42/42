/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sierpinski.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Br: cborer <cborer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/23 13:41:11 br cborer            #+#    #+#             */
/*   Updated: 2016/01/23 15:15:21 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	get_smaller_1(t_point tmp[3], t_point pt[3])
{
	tmp[0].x = (pt[0].x + pt[1].x) / 2 + (pt[1].x - pt[2].x) / 2;
	tmp[0].y = (pt[0].y + pt[1].y) / 2 + (pt[1].y - pt[2].y) / 2;
	tmp[1].x = (pt[0].x + pt[1].x) / 2 + (pt[0].x - pt[2].x) / 2;
	tmp[1].y = (pt[0].y + pt[1].y) / 2 + (pt[0].y - pt[2].y) / 2;
	tmp[2].x = (pt[0].x + pt[1].x) / 2;
	tmp[2].y = (pt[0].y + pt[1].y) / 2;
}

static void	get_smaller_2(t_point tmp[3], t_point pt[3])
{
	tmp[0].x = (pt[2].x + pt[1].x) / 2 + (pt[1].x - pt[0].x) / 2;
	tmp[0].y = (pt[2].y + pt[1].y) / 2 + (pt[1].y - pt[0].y) / 2;
	tmp[1].x = (pt[2].x + pt[1].x) / 2 + (pt[2].x - pt[0].x) / 2;
	tmp[1].y = (pt[2].y + pt[1].y) / 2 + (pt[2].y - pt[0].y) / 2;
	tmp[2].x = (pt[2].x + pt[1].x) / 2;
	tmp[2].y = (pt[2].y + pt[1].y) / 2;
}

static void	get_smaller_3(t_point tmp[3], t_point pt[3])
{
	tmp[0].x = (pt[0].x + pt[2].x) / 2 + (pt[2].x - pt[1].x) / 2;
	tmp[0].y = (pt[0].y + pt[2].y) / 2 + (pt[2].y - pt[1].y) / 2;
	tmp[1].x = (pt[0].x + pt[2].x) / 2 + (pt[0].x - pt[1].x) / 2;
	tmp[1].y = (pt[0].y + pt[2].y) / 2 + (pt[0].y - pt[1].y) / 2;
	tmp[2].x = (pt[0].x + pt[2].x) / 2;
	tmp[2].y = (pt[0].y + pt[2].y) / 2;
}

static void	tmp_init(t_point pt[3], t_point tmp[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		tmp[i].x = pt[i].x;
		tmp[i].y = pt[i].y;
		i++;
	}
}

static void	get_first(t_point tmp[3], t_point pt[3])
{
	tmp[0].x = (pt[0].x + pt[1].x) / 2;
	tmp[0].y = (pt[0].x + pt[1].x) / 2;
	tmp[1].x = (pt[0].x + pt[2].x) / 2;
	tmp[1].y = (pt[0].y + pt[2].y) / 2;
	tmp[2].x = (pt[1].x + pt[2].x) / 2;
	tmp[2].y = (pt[1].y + pt[2].y) / 2;
}

static void	draw_triangle(t_point pt[3], int n, t_map *map)
{
	t_point	tmp[3];

	tmp_init(pt, tmp);
	draw_line(pt[0], pt[1], map);
	draw_line(pt[0], pt[2], map);
	draw_line(pt[1], pt[2], map);
	if (n == 0)
	{
		get_first(tmp, pt);
		draw_triangle(tmp, 1, map);
		tmp_init(tmp, pt);
	}
	else if (n < MAX_DEPTH)
	{
		tmp_init(tmp, pt);
		get_smaller_1(tmp, pt);
		draw_triangle(tmp, n + 1, map);
		tmp_init(pt, tmp);
		get_smaller_2(tmp, pt);
		draw_triangle(tmp, n + 1, map);
		tmp_init(pt, tmp);
		get_smaller_3(tmp, pt);
		draw_triangle(tmp, n + 1, map);
	}
}

void		sierpinski(t_map *map)
{
	t_point	pt[3];

	pt[0].x = 10;
	pt[0].y = HEIGHT - 10;
	pt[1].x = WIDTH - 10;
	pt[1].y = HEIGHT - 10;
	pt[2].x = WIDTH / 2;
	pt[2].y = 10;
	draw_triangle(pt, 0, map);
}
