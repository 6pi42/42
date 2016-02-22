/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 17:28:16 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/22 18:48:38 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_map	*parse(char *file)
{
	char	*line;
	int		fd;
	int		ret;

	if ((fd = open(file, O_RDONLY)) == -1)
		ft_error_file();
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (ft_strchr())
	}
	if (ret == -1)
		ft_error_file();
	return (0);
}
