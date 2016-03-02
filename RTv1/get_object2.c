/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 13:34:09 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/02 14:21:31 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	get_spot(int fd, t_tab *tab)
{
	char	*line;
	int		ret;

	ret = get_next_line(fd, &line);
	if (ret == -1)
		ft_error_malloc();
	if ((ret = ft_strchrstr(line, "pos:")) != -1)
		tab->spot = get_vec(line + ret);
	else
		ft_error_file();
	free(line);
}
