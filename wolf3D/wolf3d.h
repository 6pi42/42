/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 14:52:44 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/12 15:30:47 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "libft.h"
# include "mlx.h"
# include <math.h>
#include <stdio.h>

# define HEIGHT 400
# define WIDTH 640
# define KEY_ESC 53
# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_P 35

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

typedef struct		s_key
{
	int				left;
	int				right;
	int				forward;
	int				behind;
	int				turn_left;
	int				turn_right;
}					t_key;

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
	double			wallhit;
	int				tex_x;
	int				tex_y;
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
	t_key			key;
	int				pause;
	int				**sky;
	int				**eagle;
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
int					key_press(int keycode, t_map *map);
void				move(t_map *map);
void				rotate(t_map *map);
int					collision(t_map *map, int a);
int					**get_texture(char *file_name, int sizel, int sizeh);

#endif
