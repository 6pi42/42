/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 11:50:07 by cboyer            #+#    #+#             */
/*   Updated: 2016/01/14 15:05:57 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft/includes/libft.h"
# include "mlx.h"
# include <fcntl.h>
# define HEIGHT 1000
# define WIDTH 1000
# define KEY_ESC 53

typedef struct		s_env
{
	void			*mlx;
	void			*win;
}					t_env;

typedef struct		s_point
{
	int				x;
	int				y;
	int				z;
	char			*color;
}					t_point;

typedef struct		s_img
{
	char			*data;
	int				size_line;
	int				bpp;
	int				endian;
	void			*img;
}					t_img;

typedef struct		s_map
{
	t_env			e;
	int				height;
	int				width;
	t_point			**map;
	t_img			img;
}					t_map;

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

t_map				*center(t_map *map);
void				ft_error(void);
t_map				*ft_parse(char *file);
void				draw(t_map *map);
void				print_grid(t_map *map);
void				pixel_put(t_map *map, int x, int y, int color);
void				init_img(t_map *map, int color);

#endif
