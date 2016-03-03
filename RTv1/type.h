/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 13:37:04 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/03 15:12:08 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H

typedef struct		s_vec
{
	double			x;
	double			y;
	double			z;
	double			r;
}					t_vec;

typedef struct		s_pos
{
	int				x;
	int				y;
}					t_pos;

typedef struct		s_sphere
{
	double			t;
	int				rgb;
	t_vec			pos;
	double			radius;
}					t_sphere;

typedef struct		s_cone
{
	double			t;
	int				rgb;
	t_vec			pos;
	double			radius;
	double			height;
}					t_cone;

typedef struct		s_cam
{
	t_vec			pos;
	t_vec			rotate;
}					t_cam;

typedef struct		s_plan
{
	double			t;
	int				rgb;
	t_vec			pos;
}					t_plan;

typedef struct		s_tab
{
	t_sphere		*sphere;
	t_cone			*cylinder;
	t_cone			*cone;
	int				nb_sphere;
	int				nb_cylinder;
	int				nb_cone;
	t_plan			plan;
	t_cam			cam;
	t_pos			screen;
	t_vec			spot;
	int				spot_v;
}					t_tab;

#endif
