/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 21:26:20 by Client            #+#    #+#             */
/*   Updated: 2016/03/29 15:59:38 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static double	get_radius(char *line)
{
	double	ret;

	while (*line == '\t' || *line == ':')
		line++;
	ret = atoi_double(line);
	if (ret == 0.0)
		ft_error_file();
	return (ret);
}

void			get_error(int j, int ret)
{
	if (ret == -1)
		ft_error_malloc();
	if (j != 4)
		ft_error_file();
}

void			get_sphere(int fd, t_tab *tab)
{
	static int	i = 0;
	int			j;
	int			h;
	int			ret;
	char		*line;

	j = 0;
	if (i >= tab->nb_sphere)
		ft_error_file();
	while (j++ != 3 && (ret = get_next_line(fd, &line)) > 0)
	{
		if ((h = ft_strchrstr(line, "rgb:")) != -1)
			tab->sphere[i].rgb = get_rgb(line + h);
		else if ((h = ft_strchrstr(line, "pos:")) != -1)
			tab->sphere[i].pos = get_vec(line + h);
		else if ((h = ft_strchrstr(line, "radius:")) != -1)
			tab->sphere[i].radius = get_radius(line + h);
		else
			ft_error_file();
		free(line);
	}
	if (ret == -1)
		ft_error_malloc();
	i++;
}

void			get_cone(int fd, t_tab *tab)
{
	static int	i = 0;
	int			j[3];
	char		*line;

	j[0] = 0;
	if (i >= tab->nb_cone)
		ft_error_file();
	while (j[0]++ != 4 && (j[1] = get_next_line(fd, &line)) > 0)
	{
		if ((j[2] = ft_strchrstr(line, "rgb:")) != -1)
			tab->cone[i].rgb = get_rgb(line + j[2]);
		else if ((j[2] = ft_strchrstr(line, "pos:")) != -1)
			tab->cone[i].pos = get_vec(line + j[2]);
		else if ((j[2] = ft_strchrstr(line, "k:")) != -1)
			tab->cone[i].k = get_radius(line + j[2]);
		else if ((j[2] = ft_strchrstr(line, "rotate:")) != -1)
			tab->cone[i].rot = get_vec(line + j[2]);
		else
			ft_error_file();
		free(line);
	}
	if (j[1] == -1)
		ft_error_malloc();
	normalize_vec(&tab->cone->rot);
	i++;
}

void			get_cylinder(int fd, t_tab *tab)
{
	static int	i = 0;
	int			j[3];
	char		*line;

	j[0] = 0;
	if (i >= tab->nb_cylinder)
		ft_error_file();
	while (j[0]++ != 4 && (j[1] = get_next_line(fd, &line)) > 0)
	{
		if ((j[2] = ft_strchrstr(line, "rgb:")) != -1)
			tab->cylinder[i].rgb = get_rgb(line + j[2]);
		else if ((j[2] = ft_strchrstr(line, "pos:")) != -1)
			tab->cylinder[i].pos = get_vec(line + j[2]);
		else if ((j[2] = ft_strchrstr(line, "radius:")) != -1)
			tab->cylinder[i].radius = get_radius(line + j[2]);
		else if ((j[2] = ft_strchrstr(line, "rotate:")) != -1)
			tab->cylinder[i].rot = get_vec(line + j[2]);
		else
			ft_error_file();
		free(line);
	}
	if (j[1] == -1)
		ft_error_malloc();
	normalize_vec(&tab->cylinder->rot);
	i++;
}
