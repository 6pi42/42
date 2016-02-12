/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertpppm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 14:07:09 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/12 15:30:48 by cboyer           ###   ########.fr       */
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
		return (0);
	i = 0;
	while (i < size)
	{
		line[i] = get_color(fd);
		printf("%d ", line[i]);
		i++;
	}
	printf("\n");
	return (line);
}

int			main(int argc, char **argv)
{
	int		i;
	int		fd;
	int		**tex;
	char	*tmp;

	i = 0;
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (0);
	if (!(tex = (int**)malloc(sizeof(int*) * ft_atoi(argv[2]))))
		return (0);
	get_next_line(fd, &tmp);
	free(tmp);
	get_next_line(fd, &tmp);
	free(tmp);
	while (i < ft_atoi(argv[2]))
	{
		tex[i] = get_line(fd, ft_atoi(argv[3]));
		i++;
	}
	return (0);
}
