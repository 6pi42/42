/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Client <Client@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 16:39:57 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/27 20:01:27 by Client           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <pthread.h>
# include "type.h"
#include <stdio.h>
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

typedef struct		s_map
{
	t_env			e;
	t_img			img;
	t_tab			*tab;
}					t_map;

typedef struct		s_args
{
	t_map			*map;
	int				min;
	int				max;
}					t_args;

void				pixel_put(t_map *map, int x, int y, int color);
int					get_hex_color(t_map *map, int x, int y);

t_tab				*parse(char *file);
int					ft_strchrstr(char *str, char *chr);
double				atoi_double(char *line);
int					atoi_hex(char *line);

void				multi_threading(t_map *map, void *f);
void				raytracer(t_map *map);
t_vec				init_ray(t_map *map, int x, int y);

void				get_inter_sphere(t_sphere *s, int i, int j, t_map *map);
int					get_smaller_sphere(t_sphere *sphere, int c);
void				*nearest_sphere(int y, int x, t_map *map,
	t_sphere *sphere, int c);
void				*plan(int y, int x, t_map *map);

int					expose_hook(t_map *map);
int					key_hook(int keycode, t_map *map);

t_pos				get_screen(char *line);
t_vec				get_vec(char *line);
t_plan				get_plan(int fd);
int					get_rgb(char *line);

int					get_nb_struct(char *file, char *str);
void				get_sphere(int fd, t_tab *tab);
void				get_cylinder(int fd, t_tab *tab);
void				get_cone(int fd, t_tab *tab);
t_cam				get_cam(int fd);

void				ft_error(void);
void				ft_error_file(void);
void				ft_error_malloc(void);
void				ft_error_mlx(void);
void				ft_error_arg(void);

#endif
