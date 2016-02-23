/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Client <Client@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 13:37:04 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/23 21:55:22 by Client           ###   ########.fr       */
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

typedef struct		s_tab
{
	t_sphere		*sphere;
	int				nb_sphere;
	int				plan;
	t_vec			cam;
	t_pos			screen;
}					t_tab;

#endif
