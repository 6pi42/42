/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 16:11:53 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/04 18:12:43 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "libft.h"
# include "mlx.h"
# include <math.h>
#include <stdio.h>

# define HEIGHT 200
# define WIDTH 320
# define KEY_ESC 53
# define UNIT 64

typedef struct		s_env
{
	void			*mlx;
	void			*win;
}					t_env;

typedef struct		s_img
{
	char			*data;
	int				size_line;
	int				bpp;
	int				endian;
	void			*img;
}					t_img;

typedef struct		s_vec
{
	double			x;
	double			y;
}					t_vec;

typedef struct		s_point
{
	int				x;
	int				y;
	int				z;
}					t_point;

typedef struct		s_dda
{
	double			x;
	double			y;
	t_vec			dir;
	t_point			step;
	t_point			mapcoord;
	t_vec			side;
	t_vec			delta;
	int				sidehit;
	double			walldist;
}					t_dda;

typedef struct		s_bres
{
	int				dx;
	int				dy;
	int				e;
	int				sx;
	int				sy;
	int				inc1;
	int				inc2;
}					t_bres;

typedef	struct		s_player
{
	t_vec		dir;
	t_vec		pos;
}					t_player;

typedef struct		s_map
{
	t_env			e;
	int				height;
	int				width;
	t_img			img;
	t_point			**map;
	t_player		player;
	t_vec			plane;
}					t_map;

void				ft_error(void);
void				pixel_put(t_map *map, int x, int y, int color);
void				init_img(t_map *map, int color);
int					key_hook(int keycode, t_map *map);
void				draw(t_map *map);
void				draw_line(t_point pt1, t_point pt2, t_map *map);
int					motion_notify(int x, int y, t_map *map);
int					expose_hook(t_map *map);
t_map				*ft_parse(char *file);
void				raycasting(t_map *map);

#endif
