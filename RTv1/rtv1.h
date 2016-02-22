/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 16:39:57 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/22 18:28:40 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <pthread.h>

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

typedef struct		s_cam
{
	double			x;
	double			y;
	double			z;
}

typedef struct		s_pos
{
	int				x;
	int				y;
}					t_pos;

typedef struct		s_rgb
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}					t_rgb;

typedef struct		s_sphere
{

}					t_sphere;

typedef struct		s_map
{
	t_env			e;
	t_img			img;
	t_cam			cam;
	t_pos			screen;
}					t_map;

typedef struct		s_args
{
	t_map			*map;
	int				min;
	int				max;
}					t_args;

void				pixel_put(t_map *map, int x, int y, int color);
int					get_hex_color(t_map *map, int x, int y);

t_map				*parse(char *file);
void				multi_threading(t_map *map, void *f);
void				raytracer(void *args);

void				ft_error(void);
void				ft_error_file(void);
void				ft_error_malloc(void);
void				ft_error_mlx(void);
void				ft_error_arg(void);

#endif
