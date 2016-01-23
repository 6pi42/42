/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 11:50:07 by cboyer            #+#    #+#             */
/*   Updated: 2016/01/23 16:19:20 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "libft.h"
# include "mlx.h"
#include <stdio.h>
# define HEIGHT 1000
# define WIDTH 1000
# define KEY_ESC 53

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
}					t_map;

void				ft_error(void);
void				pixel_put(t_map *map, int x, int y, int color);
void				init_img(t_map *map, int color);
void				mandelbrot(t_map *map, int max_iter);
void				draw(t_map *map);

#endif
