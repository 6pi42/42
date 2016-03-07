/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 16:39:57 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/07 16:04:07 by cboyer           ###   ########.fr       */
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
# define NB_OBJ 4

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
void				normalize_vec(t_vec *vec);

t_tab				*parse(char *file);
int					ft_strchrstr(char *str, char *chr);
double				atoi_double(char *line);
int					atoi_hex(char *line);
int					correct_line(char *line);

void				multi_threading(t_map *map, void *f);
void				raytracer(t_map *map);
t_vec				init_ray(t_map *map, int x, int y);
t_vec				init_ray_lumos(t_map *map, int x, int y, void *obj);

void				*nearest_sphere(t_vec ray, t_map *map, t_sphere *sphere,
	t_vec org);
void				*nearest_plan(t_vec org, t_vec ray, t_map *map);
int					plan_lumos(t_map *map, t_plan *plan, t_vec ray);
void				*smaller_void(void **st);
int					sphere_lumos(t_map *map, t_sphere *sphere, t_vec ray);
t_vec				get_light_ray(void *obj, t_vec ray, t_map *map);
int					shadow(t_map *map, void *obj, t_vec ray);
void				*nearest_cyl(t_vec ray, t_map *map, t_cone *cyl, t_vec org);
void				*nearest_cone(t_vec ray, t_map *map, t_cone *cone,
	t_vec org);
int					light_rgb(int rgb, double angle);
int					add_rgb(int rgb, double coef);
t_vec				get_normal_sphere(t_sphere *sphere, t_vec ray, t_map *map);
int					sphere_reflexion(t_map *map, t_sphere *sphere, t_vec ray, int rgb);

int					expose_hook(t_map *map);
int					key_hook(int keycode, t_map *map);

t_pos				get_screen(char *line);
t_vec				get_vec(char *line);
void				get_plan(int fd, t_tab *tab);
int					get_rgb(char *line);

int					get_nb_struct(char *file, char *str);
void				get_sphere(int fd, t_tab *tab);
void				get_cylinder(int fd, t_tab *tab);
void				get_cone(int fd, t_tab *tab);
t_cam				get_cam(int fd);
void				get_spot(int fd, t_tab *tab);

void				ft_error(void);
void				ft_error_file(void);
void				ft_error_malloc(void);
void				ft_error_mlx(void);
void				ft_error_arg(void);

double				length_vec(t_vec vec);
void				normalize_vec(t_vec *vec);
double				dot_vec(t_vec a, t_vec b);
t_vec				cross_product_vec(t_vec a, t_vec b);
t_vec				mult_int_vec(t_vec a, double i);
t_vec				sous_vec(t_vec a, t_vec b);

#endif
