/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 13:37:04 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/24 14:34:34 by cboyer           ###   ########.fr       */
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
	double			radius;
	t_vec			pos;
	int				rgb;
}					t_sphere;

typedef struct		s_cone
{
	double				radius;
	double				height;
	int					rgb;
	t_vec				pos;
}					t_cone;

typedef struct		s_tab
{
	t_sphere		*sphere;
	t_cone			*cylinder;
	t_cone			*cone;
	int				nb_sphere;
	int				nb_cylinder;
	int				nb_cone;
	int				plan;
	t_vec			cam;
	t_pos			screen;
}					t_tab;

#endif
