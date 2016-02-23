/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Client <Client@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 17:28:16 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/23 21:40:12 by Client           ###   ########.fr       */
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
	t_tab	*tab;
	int		i;

	tab = (t_tab*)malloc(sizeof(t_tab));
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_error_file();
	tab->sphere = (t_sphere*)malloc(sizeof(t_sphere) * get_nb_sphere(fd));
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		printf("%s\n", line);
		if ((i = ft_strchrstr(line, "\tcamera:\t")) != -1)
			tab->cam = get_vec_cam(line + i);
		if ((i = ft_strchrstr(line, "\tscreen:\t")) != -1)
			tab->screen = get_screen(line + i);
		if ((i = ft_strchrstr(line, "\tplan:")) != -1)
			tab->plan = get_plan(fd);
		if ((i = ft_strchrstr(line, "\tsphere:")) != -1)
			get_sphere(fd, tab);
		free(line);
	}
	if (ret == -1)
		ft_error_file();
	return (0);
}
