/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppmreader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 14:07:09 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/10 14:51:47 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	get_color(int fd)
{
	char	*line;
	int		red;
	int		green;
	int		blue;

	get_next_line(fd, &line);
	red = ft_atoi(line);
	free(line);
	get_next_line(fd, &line);
	green = ft_atoi(line);
	free(line);
	get_next_line(fd, &line);
	blue = ft_atoi(line);
	free(line);
	return (256 * 256 * red + 256 * green + blue);
}

static int	*get_line(int fd, int size)
{
	int i;
	int *line;

	if (!(line = (int*)malloc(sizeof(int) * (size))))
		return (NULL);
	i = 0;
	while (i < size)
	{
		line[i] = get_color(fd);
		i++;
	}
	return (line);
}

int			**get_texture(char *file_name, int sizel, int sizeh)
{
	int		i;
	int		fd;
	int		**tex;
	char	*tmp;

	i = 0;
	if ((fd = open(file_name, O_RDONLY)) == -1)
		return (NULL);
	if (!(tex = (int**)malloc(sizeof(int*) * sizeh)))
		return (NULL);
	get_next_line(fd, &tmp);
	free(tmp);
	get_next_line(fd, &tmp);
	free(tmp);
	while (i < sizeh)
	{
		tex[i] = get_line(fd, sizel);
		i++;
	}
	return (tex);
}
