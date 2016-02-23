/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Client <Client@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 17:28:16 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/23 22:00:36 by Client           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		ft_strchrstr(char *str, char *chr)
{
	size_t	i;
	int		h;

	i = 0;
	h = 0;
	while (str[h] && chr[i])
	{
		if (str[h] == chr[i])
			i++;
		else
			i = 0;
		if (i == ft_strlen(chr))
			return (h);
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

void   print_sphere(t_tab *tab)
{
	int i;

	i = 0;
	while (i < tab->nb_sphere)
	{
		printf("rayon: %f\n", tab->sphere[i].radius);
		printf("pos: x %f y %f z %f\n", tab->sphere[i].pos.x,tab->sphere[i].pos.y,
			tab->sphere[i].pos.z);
		printf("rgb: %d\n", tab->sphere[i].rgb);
		i++;
	}
}

t_tab	*parse(char *file)
{
	char	*line;
	int		ret;
	int		fd;
	t_tab	*tab;
	int		i;

	if (!(tab = (t_tab*)malloc(sizeof(t_tab))))
		ft_error_malloc();
	tab->nb_sphere = get_nb_sphere(file);
	if (!(tab->sphere = (t_sphere*)malloc(sizeof(t_sphere) * tab->nb_sphere)))
		ft_error_malloc();
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_error_file();
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if ((i = ft_strchrstr(line, "camera:")) != -1)
			tab->cam = get_vec_cam(line + i);
		if ((i = ft_strchrstr(line, "screen:")) != -1)
			tab->screen = get_screen(line + i);
		if ((i = ft_strchrstr(line, "plan:")) != -1)
			tab->plan = get_plan(fd);
		if ((i = ft_strchrstr(line, "sphere:")) != -1)
			get_sphere(fd, tab);
		free(line);
	}
	print_sphere(tab);
	if (ret == -1)
		ft_error_file();
	close(fd);
	return (0);
}
