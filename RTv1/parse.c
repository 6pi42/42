/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 17:28:16 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/02 14:21:21 by cboyer           ###   ########.fr       */
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
			return (h + 1);
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

int		get_nb_struct(char *file, char *str)
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
		if (ft_strchrstr(line, str) != -1)
			i++;
		free(line);
	}
	if (ret == -1)
		ft_error_arg();
	close(fd);
	return (i);
}

t_tab	*init_tab(char *file)
{
	t_tab	*tab;

	if (!(tab = (t_tab*)malloc(sizeof(t_tab))))
		ft_error_malloc();
	tab->nb_sphere = get_nb_struct(file, "\tsphere:");
	tab->nb_cylinder = get_nb_struct(file, "\tcylinder:");
	tab->nb_cone = get_nb_struct(file, "\tcone");
	if (!(tab->sphere = (t_sphere*)malloc(sizeof(t_sphere) * tab->nb_sphere)))
		ft_error_malloc();
	if (!(tab->cylinder = (t_cone*)malloc(sizeof(t_cone) * tab->nb_cylinder)))
		ft_error_malloc();
	if (!(tab->cone = (t_cone*)malloc(sizeof(t_cone) * tab->nb_cone)))
		ft_error_malloc();
	return (tab);
}

t_tab	*parse(char *file)
{
	char	*line;
	int		ret;
	int		fd;
	t_tab	*tab;
	int		i;

	tab = init_tab(file);
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_error_file();
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if ((i = ft_strchrstr(line, "camera:")) != -1)
			tab->cam = get_cam(fd);
		else if ((i = ft_strchrstr(line, "screen:")) != -1)
			tab->screen = get_screen(line + i);
		else if ((i = ft_strchrstr(line, "plan:")) != -1)
			tab->plan = get_plan(fd);
		else if ((i = ft_strchrstr(line, "sphere:")) != -1)
			get_sphere(fd, tab);
		else if ((i = ft_strchrstr(line, "cone:")) != -1)
			get_cone(fd, tab);
		else if ((i = ft_strchrstr(line, "cylinder:")) != -1)
			get_cylinder(fd, tab);
		else if ((i = ft_strchrstr(line, "spot:")) != -1)
			get_spot(fd, tab);
		free(line);
	}
	if (ret == -1)
		ft_error_file();
	close(fd);
	return (tab);
}
