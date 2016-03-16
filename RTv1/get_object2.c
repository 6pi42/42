/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 13:34:09 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/16 14:55:23 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	get_spot(int fd, t_tab *tab)
{
	char		*line;
	int			ret;
	static int	i = 0;

	ret = get_next_line(fd, &line);
	if (ret == -1)
		ft_error_malloc();
	if ((ret = ft_strchrstr(line, "pos:")) != -1)
		tab->spot[i] = get_vec(line + ret);
	else
		ft_error_file();
	free(line);
	i++;
}

int		correct_line(char *line)
{
	if (ft_strchrstr(line, "scene:") != -1)
		return (1);
	if (ft_strchrstr(line, "object:") != -1)
		return (1);
	if (ft_strlen(line) == 1 && line[0] == '\n')
		return (1);
	if (ft_strlen(line) == 0)
		return (1);
	return (0);
}
