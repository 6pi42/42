/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 16:03:17 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/27 14:51:10 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec	get_vec(char *line)
{
	char	**tab;
	t_vec	vec;
	int		i;

	i = 0;
	while (*line == '\t')
		line++;
	tab = ft_strsplit(line, ' ');
	while (tab[i])
		i++;
	if (i != 3)
		ft_error_file();
	vec.x = atoi_double(tab[0]);
	vec.y = atoi_double(tab[1]);
	vec.z = atoi_double(tab[2]);
	while (tab[i])
		free(tab[i]);
	free(tab);
	return (vec);
}

t_pos	get_screen(char *line)
{
	char	**tab;
	int		i;
	t_pos	screen;

	i = 0;
	while (*line == '\t' || *line == ' ')
		line++;
	tab = ft_strsplit(line, ' ');
	while (tab[i])
		i++;
	if (i != 2)
		ft_error_file();
	screen.x = ft_atoi(tab[0]);
	screen.y = ft_atoi(tab[1]);
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (screen);
}

t_cam	get_cam(int fd)
{
	int		j;
	t_cam	cam;
	int		ret;
	char	*line;
	int		i;

	j = 0;
	while ((ret = get_next_line(fd, &line)) > 0 && j != 1)
	{
		if ((i = ft_strchrstr(line, "pos:")) != -1)
			cam.pos = get_vec(line + i);
		else if ((i = ft_strchrstr(line, "rotate:")) != -1)
			cam.rotate = get_vec(line + i);
		else
			ft_error_file();
		j++;
	}
	if (ret == -1)
		ft_error();
	return (cam);
}

int		get_rgb(char *line)
{
	line = ft_strchr(line, 'x') != NULL ? ft_strchr(line, 'x') + 1: NULL;
	if (!line)
		ft_error_file();
	return (atoi_hex(line));
}

t_plan	get_plan(int fd)
{
	char	*line;
	int		ret;
	int		i;
	int		j;
	t_plan	plan;

	j = 0;
	while ((ret = get_next_line(fd, &line)) > 0 && j != 1)
	{
		if ((i = ft_strchrstr(line, "rgb:")) != -1)
			plan.rgb = get_rgb(line + i);
		else if ((i = ft_strchrstr(line, "rotate:")) != -1)
			plan.pos = get_vec(line + i);
		else
			ft_error_file();
		free(line);
		j++;
	}
	if (ret == -1)
		ft_error();
	return (plan);
}
