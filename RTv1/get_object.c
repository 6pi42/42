/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Client <Client@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 21:26:20 by Client            #+#    #+#             */
/*   Updated: 2016/02/23 22:07:29 by Client           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


int				get_nb_sphere(char *file)
{
	int		i;
	char	*line;
	int		ret;
	int		fd;

	if ((fd = open(file, O_RDONLY)) == -1)
		ft_error_file();
	i = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (ft_strchrstr(line, "\tsphere:") != -1)
			i++;
		free(line);
	}
	if (ret == -1)
		ft_error_arg();
	close(fd);
	return (i);
}

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

void			get_sphere(int fd, t_tab *tab)
{
	static int	i = 0;
	int			j;
	int			h;
	int			ret;
	char		*line;

	j = 0;
	while ((ret = get_next_line(fd, &line)) > 0 && j != 3)
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
	if (j != 3)
		ft_error_file();
}
