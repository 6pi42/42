/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 11:50:07 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/09 16:30:07 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
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
}					t_point;

typedef struct		s_comp
{
	double			r;
	double			i;
}					t_comp;

typedef struct		s_map
{
	t_env			e;
	int				height;
	int				width;
	t_img			img;
	double			zoom;
	char			*mode;
	t_comp			julia;
	t_point			mouse;
	int				max_iter;
	int				pow;
	int				c;
}					t_map;

void				ft_print_choices(void);
void				ft_error(void);
void				pixel_put(t_map *map, int x, int y, int color);
void				init_img(t_map *map, int color);
void				mandelbrot(t_map *map);
void				draw(t_map *map);
void				julia(t_map *map);
void				burning_ship(t_map *map);
void				rabbit(t_map *map);
int					key_hook(int keycode, t_map *map);
int					motion_notify(int x, int y, t_map *map);
int					expose_hook(t_map *map);
void				siegel(t_map *map);
int					get_c(int i);
int					get_c2(int i);
int					buttonpress_hook(int button, int x, int y, t_map *map);
char				*ft_itoa_base(int n, int base);

#endif
