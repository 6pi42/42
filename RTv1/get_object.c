/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 21:26:20 by Client            #+#    #+#             */
/*   Updated: 2016/02/27 14:55:14 by cboyer           ###   ########.fr       */
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
	if (j != 3)
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
	while (j != 3 && (ret = get_next_line(fd, &line)) > 0)
	{
		if ((h = ft_strchrstr(line, "rgb:")) != -1)
			tab->sphere[i].rgb = get_rgb(line + h);
		else if ((h = ft_strchrstr(line, "pos:")) != -1)
			tab->sphere[i].pos = get_vec(line + h);
		else if ((h = ft_strchrstr(line, "radius:")) != -1)
			tab->sphere[i].radius = get_radius(line + h);
		else
			ft_error_file();
		j++;
		free(line);
	}
	if (ret == -1)
		ft_error_malloc();
	i++;
}

void			get_cone(int fd, t_tab *tab)
{
	static int	i = 0;
	int			j;
	int			h;
	int			ret;
	char		*line;

	j = 0;
	if (i >= tab->nb_cone)
		ft_error_file();
	while (j != 3 && (ret = get_next_line(fd, &line)) > 0)
	{
		if ((h = ft_strchrstr(line, "rgb:")) != -1)
			tab->cone[i].rgb = get_rgb(line + h);
		else if ((h = ft_strchrstr(line, "pos:")) != -1)
			tab->cone[i].pos = get_vec(line + h);
		else if ((h = ft_strchrstr(line, "radius:")) != -1)
			tab->cone[i].radius = get_radius(line + h);
		else if ((h = ft_strchrstr(line, "height:")) != -1)
			tab->cone[i].height = get_radius(line + h);
		else
			ft_error_file();
		j++;
		free(line);
	}
	get_error(j, ret);
	i++;
}

void			get_cylinder(int fd, t_tab *tab)
{
	static int	i = 0;
	int			j;
	int			h;
	int			ret;
	char		*line;

	j = 0;
	if (i >= tab->nb_cylinder)
		ft_error_file();
	while ((ret = get_next_line(fd, &line)) > 0 && j != 3)
	{
		if ((h = ft_strchrstr(line, "rgb:")) != -1)
			tab->cylinder[i].rgb = get_rgb(line + h);
		else if ((h = ft_strchrstr(line, "pos:")) != -1)
			tab->cylinder[i].pos = get_vec(line + h);
		else if ((h = ft_strchrstr(line, "radius:")) != -1)
			tab->cylinder[i].radius = get_radius(line + h);
		else if ((h = ft_strchrstr(line, "height:")) != -1)
			tab->cylinder[i].height = get_radius(line + h);
		else
			ft_error_file();
		j++;
		free(line);
	}
	get_error(j, ret);
	i++;
}
