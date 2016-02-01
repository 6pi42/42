/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 11:50:10 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/01 21:12:59 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		get_height(char *file)
{
	int		height;
	int		fd;
	int		ret;
	char	buf[2];

	height = 0;
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_error();
	while ((ret = read(fd, &buf, 1)))
	{
		if (buf[0] == '\n')
			height++;
	}
	if (ret == -1)
		ft_error();
	if (close(fd) == -1)
		ft_error();
	return (height);
}

static	t_point	set_point(int x, int y, char *value)
{
	t_point	tmp;

	tmp.z = ft_atoi(value);
	if ((ft_strchr(value, ',')) && (ft_strlen(ft_strchr(value, ',')) == 10))
		tmp.color = ft_strsub(ft_strchr(value, ','), 0, 10);
	else
		tmp.color = NULL;
	tmp.y = y;
	tmp.x = x;
	free(value);
	return (tmp);
}

static	t_point	*parse_line(char **line, int height, int *width)
{
	t_point	*tmp;
	int		i;

	i = 0;
	while (line[i])
		i++;
	if (!(tmp = (t_point*)malloc(sizeof(t_point) * i)))
		ft_error();
	i = 0;
	while (line[i])
	{
		tmp[i] = set_point(i, height, line[i]);
		i++;
	}
	*width = i;
	free(line);
	line = 0;
	return (tmp);
}

static	t_point	**get_map(char *file, int *height, int *width)
{
	t_point	**map;
	char	*line;
	int		i;
	int		fd;

	i = 0;
	*height = get_height(file);
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_error();
	if (!(map = (t_point**)malloc(sizeof(t_point*) * *height)))
		ft_error();
	while (get_next_line(fd, &line) == 1)
	{
		map[i] = parse_line(ft_strsplit(line, ' '), i, width);
		free(line);
		line = NULL;
		i++;
	}
	if (close(fd) == -1)
		ft_error();
	return (map);
}

t_map			*ft_parse(char *file)
{
	t_map	*map;
	int		height;
	int		width;

	if (!(map = (t_map*)malloc(sizeof(t_map))))
		return (NULL);
	if (!(map->map = get_map(file, &height, &width)))
		return (NULL);
	map->height = height;
	map->width = width;
	copy_cart(map);
	map = center(map);
	return (map);
}
