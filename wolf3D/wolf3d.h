/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 16:11:53 by cboyer            #+#    #+#             */
/*   Updated: 2016/01/26 11:32:29 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "libft.h"
# include "mlx.h"
# include <math.h>

# define HEIGHT 1000
# define WIDTH 1000
# define KEY_ESC 53
# define MAX_DEPTH 8
# define MAX_ITER 100

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

typedef struct		s_point
{
	int				x;
	int				y;
	int				z;
}					t_point;

typedef struct		s_comp
{
	double			r;
	double			i;
}					t_comp;

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

typedef struct		s_map
{
	t_env			e;
	int				height;
	int				width;
	t_img			img;
	t_point			**map;
}					t_map;

void				ft_error(void);
void				pixel_put(t_map *map, int x, int y, int color);
void				init_img(t_map *map, int color);
void				draw(t_map *map);
void				draw_line(t_point pt1, t_point pt2, t_map *map);
int					key_hook(int keycode, t_map *map);
int					motion_notify(int x, int y, t_map *map);
int					expose_hook(t_map *map);
int					circulate_notify_down(t_map *map);
int					circulate_notify_up(t_map *map);
t_map				*ft_parse(char *file);

#endif
