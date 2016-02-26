/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 11:26:30 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/25 19:01:32 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	get_hex_color(t_map *map, int x, int y)
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;

	red = map->img.data[y * map->img.size_line + (x * map->img.bpp) / 8];
	green = map->img.data[y * map->img.size_line + (x * map->img.bpp) / 8 + 1];
	blue = map->img.data[y * map->img.size_line + (x * map->img.bpp) / 8 + 2];
	return (blue << 16 | green << 8 | red);
}

int	atoi_hex(char *line)
{
	int	nbr;
	int	i;
	int	add;

	i = 0;
	nbr = 0;
	if (ft_strlen(&line[i]) > 8)
		ft_error_file();
	while ((line[i] >= '0' && line[i] <= '9')
		|| (line[i] >= 'A' && line[i] <= 'F'))
	{
		if (line[i] > '9')
			add = 9 + line[i] - 'A' + 1;
		else
			add = line[i] - '0';
		nbr = nbr * 16 + add;
		i++;
	}
	return (nbr);
}
