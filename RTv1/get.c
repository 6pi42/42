/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 16:03:17 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/24 13:48:27 by cboyer           ###   ########.fr       */
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
	while (*line == '\t')
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

t_vec	get_vec_cam(char *line)
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
	if (i != 4)
		ft_error_file();
	vec.x = atoi_double(tab[0]);
	vec.y = atoi_double(tab[1]);
	vec.z = atoi_double(tab[2]);
	vec.r = atoi_double(tab[3]);
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (vec);
}

int		get_rgb(char *line)
{
	line = ft_strchr(line, 'x') != NULL ? ft_strchr(line, 'x') + 1 : NULL;
	if (!line)
		ft_error_file();
	return (atoi_hex(line));
}

int		get_plan(int fd)
{
	char	*line;
	int		ret;
	int		rgb;

	rgb = 0;
	ret = get_next_line(fd, &line);
	if (ret == -1)
		ft_error();
	if (ft_strchrstr(line, "rgb"))
		rgb = get_rgb(line);
	else
		ft_error_file();
	free(line);
	return (rgb);
}
