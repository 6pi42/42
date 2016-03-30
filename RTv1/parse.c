/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 17:28:16 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/30 16:15:47 by cboyer           ###   ########.fr       */
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
	tab->nb_cone = get_nb_struct(file, "\tcone:");
	tab->nb_plan = get_nb_struct(file, "\tplan:");
	tab->nb_spot = get_nb_struct(file, "\tspot:");
	if (tab->nb_sphere &&
		!(tab->sphere = (t_sphere*)malloc(sizeof(t_sphere) * tab->nb_sphere)))
		ft_error_malloc();
	if (tab->nb_plan &&
		!(tab->plan = (t_plan*)malloc(sizeof(t_plan) * tab->nb_plan)))
		ft_error_malloc();
	if (tab->nb_cylinder &&
		!(tab->cylinder = (t_cyl*)malloc(sizeof(t_cyl) * tab->nb_cylinder)))
		ft_error_malloc();
	if (tab->nb_cone &&
		!(tab->cone = (t_cone*)malloc(sizeof(t_cone) * tab->nb_cone)))
		ft_error_malloc();
	if (tab->nb_spot &&
		!(tab->spot = (t_vec*)malloc(sizeof(t_vec) * tab->nb_spot)))
		ft_error_malloc();
	return (tab);
}

void	get_key_words(t_tab *tab, int fd, char *line)
{
	int	i;

	if ((i = ft_strchrstr(line, "camera:")) != -1)
		tab->cam = get_cam(fd);
	else if ((i = ft_strchrstr(line, "screen:")) != -1)
		tab->screen = get_screen(line + i);
	else if ((i = ft_strchrstr(line, "plan:")) != -1)
		get_plan(fd, tab);
	else if ((i = ft_strchrstr(line, "sphere:")) != -1)
		get_sphere(fd, tab);
	else if ((i = ft_strchrstr(line, "cone:")) != -1)
		get_cone(fd, tab);
	else if ((i = ft_strchrstr(line, "cylinder:")) != -1)
		get_cylinder(fd, tab);
	else if ((i = ft_strchrstr(line, "spot:")) != -1)
		get_spot(fd, tab);
	else if (!(correct_line(line)))
		ft_error_file();
}

t_tab	*parse(char *file)
{
	char	*line;
	int		ret;
	int		fd;
	t_tab	*tab;

	tab = init_tab(file);
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_error_file();
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		get_key_words(tab, fd, line);
		free(line);
	}
	if (ret == -1)
		ft_error_file();
	close(fd);
	return (tab);
}
