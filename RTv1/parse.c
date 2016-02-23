/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 17:28:16 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/23 16:31:05 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		ft_strchrstr(char *str, char *chr)
{
	size_t	i;
	int		j;
	int		h;

	i = 0;
	h = 0;
	while (str[h] && chr[i])
	{
		if (str[h] == chr[i])
		{
			j = h;
			i++;
		}
		else
			i = 0;
		if (i == ft_strlen(chr))
			return (j);
		h++;
	}
	return (-1);
}

double	atoi_double(char *line)
{
	double	ent;
	double	dec;

	ent = (double)ft_atoi(line);
	line = ft_strchr(line, '.') != NULL ? ft_strchr(line, '.') + 1 : NULL;
	if (!line)
		ft_error_file();
	dec = (double)ft_atoi(line);
	while (dec >= 1.0)
		dec = dec / 10.0;
	return (dec + ent);
}

t_tab	*parse(char *file)
{
	char	*line;
	int		ret;
	int		fd;
	int		i;
	t_tab	*tab;

	tab = (t_tab*)malloc(sizeof(t_tab));
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_error_file();
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if ((i = ft_strchrstr(line, "\tcamera:\t")) != -1)
		{
			line += i;
			tab->cam = get_vec_cam(line);
		}
		if ((i = ft_strchrstr(line, "\tscreen:\t")) != -1)
		{
			line += i;
			tab->screen = get_screen(line);
		}
		if ((i = ft_strchrstr(line, "\tplan:")))
			tab->plan = get_plan(fd);
		printf("OK\n");
		free(line);
	}
	if (ret == -1)
		ft_error_file();
	return (0);
}
