/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 13:37:04 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/30 15:54:51 by cboyer           ###   ########.fr       */
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
	t_vec			norm;
	t_vec			pos;
	t_vec			rot;
	double			radius;
}					t_sphere;

typedef struct		s_cone
{
	double			t;
	int				rgb;
	t_vec			norm;
	t_vec			pos;
	t_vec			rot;
	double			k;
}					t_cone;

typedef struct		s_cyl
{
	double			t;
	int				rgb;
	t_vec			norm;
	t_vec			pos;
	t_vec			rot;
	double			radius;
}					t_cyl;

typedef struct		s_cam
{
	t_vec			pos;
	t_vec			rotate;
}					t_cam;

typedef struct		s_plan
{
	double			t;
	int				rgb;
	t_vec			norm;
	t_vec			pos;
}					t_plan;

typedef struct		s_tab
{
	t_sphere		*sphere;
	t_cone			*cone;
	t_plan			*plan;
	t_cyl			*cylinder;
	int				nb_sphere;
	int				nb_cylinder;
	int				nb_cone;
	int				nb_plan;
	int				nb_spot;
	t_cam			cam;
	t_pos			screen;
	t_vec			*spot;
	t_vec			*spot_a;
}					t_tab;

#endif
