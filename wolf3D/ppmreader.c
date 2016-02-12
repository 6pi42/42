/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppmreader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 14:07:09 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/12 15:30:49 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	*get_line(int fd, int size)
{
	int 	i;
	char 	**line;
	char 	*tmp;
	int		*line_int;

	if (!(line = (char**)malloc(sizeof(char*) * (size))))
		return (0);
	if (!(line_int = (int*)malloc(sizeof(int) * (size))))
		return (0);
	get_next_line(fd, &tmp);
	line = ft_strsplit(tmp, ' ');
	free(tmp);
	i = 0;
	while (i < size)
	{
		line_int[i] = ft_atoi(line[i]);
		i++;
	}
	return (line_int);
}

int			**get_texture(char *file_name, int sizel, int sizeh)
{
	int		i;
	int		fd;
	int		**tex;

	i = 0;
	if ((fd = open(file_name, O_RDONLY)) == -1)
		return (NULL);
	if (!(tex = (int**)malloc(sizeof(int*) * sizeh)))
		return (NULL);
	while (i < sizeh)
	{
		tex[i] = get_line(fd, sizel);
		i++;
	}
	return (tex);
}
