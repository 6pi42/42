/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 16:39:57 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/30 14:37:05 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <pthread.h>
# include "type.h"
# include <float.h>
# define KEY_ESC 53
# define NB_OBJ 4
# define FOV 60
#include <stdio.h>

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

struct				s_tab_f
{
	int				(*f)(t_map *map, void *ob, t_vec ray, int rgb);
};

void				pixel_put(t_map *map, int x, int y, int color);
int					get_hex_color(t_map *map, int x, int y);
void				multi_threading(t_map *map, void *f);

t_tab				*parse(char *file);
int					ft_strchrstr(char *str, char *chr);
double				atoi_double(char *line);
int					atoi_hex(char *line);
int					correct_line(char *line);
double				to_rad(double a);

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

void				raytracer(t_map *map);
t_vec				init_ray(t_map *map, double x, double y);
t_vec				get_light_ray(void *ob, t_vec ray, t_vec inter, t_map *map);
void				multi_sampling(int x, int y, t_map *map);

int					shadow(t_map *map, void *obj, t_vec ray[3], t_vec spot);
int					get_shadow(t_map *map, void *obj, t_vec ray[3], int rgb);
int					get_shadow_color(int color, int nb);
int					shadow_rgb(int rgb, double angle);

void				*nearest_cyl(t_vec ray, t_map *map, int n, t_vec org);
void				*nearest_cone(t_vec ray, t_map *map, int n, t_vec org);
void				*nearest_plan(t_vec org, t_vec ray, t_map *map);
void				nearest_obj(t_map *map, t_vec ray, t_vec org, void **st);
void				*nearest_sphere(t_vec ray, t_map *m, int n, t_vec o);
void				*smaller_void(void **st);

int					light_rgb(int rgb, double angle);
int					reflection(int rgb, double dot);

t_vec				get_normal_sphere(t_sphere *sphere, t_vec ray, t_map *map);
int					sphere_reflexion(t_map *m, t_sphere *s, t_vec ray, int rgb);
t_vec				intersection(void *obj, t_vec ray, t_vec org);
int					multi_spot(void **st, void *ob, t_vec ray[3], t_map *map);

int					expose_hook(t_map *map);
int					key_hook(int keycode, t_map *map);
int					red_cross(t_map *map);

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
t_vec				add_vec(t_vec a, t_vec b);
t_vec				sous_vec_n(t_vec b, t_vec a);
void				normalize_vec(t_vec *vec);

int					sphere_lumos_spec(t_map *map, void *s, t_vec ray, int rgb);
int					sphere_lumos_diff(t_map *map, void *s, t_vec ray, int rgb);
int					cyl_lumos_spec(t_map *map, void *cyl, t_vec ray, int rgb);
int					cyl_lumos_diff(t_map *map, void *cyl, t_vec ray, int rgb);
int					plan_lumos(t_map *map, void *plan, t_vec ray, int rgb);
int					cone_lumos_spec(t_map *map, void *obj, t_vec intr, int rgb);
int					cone_lumos_diff(t_map *map, void *obj, t_vec intr, int rgb);

int					moy_rgb(int *rgb, int len);
int					add_rgb(int rgb);
int					max_rgb(int *rgb, int len);
int					min_rgb(int *rgb, int len);
int					mul_rgb(int rgb, double coef);
int					specular(int rgb, int lumos, double dot);

#endif
