/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 11:26:30 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/29 13:39:35 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	to_rad(double a)
{
	return (a * M_PI / 180.0);
}

int		get_hex_color(t_map *map, int x, int y)
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;

	red = map->img.data[y * map->img.size_line + (x * map->img.bpp) / 8];
	green = map->img.data[y * map->img.size_line + (x * map->img.bpp) / 8 + 1];
	blue = map->img.data[y * map->img.size_line + (x * map->img.bpp) / 8 + 2];
	return (blue << 16 | green << 8 | red);
}

int		atoi_hex(char *line)
{
	int	nbr;
	int	i;
	int	add;

	i = -1;
	nbr = 0;
	while (line[i++])
		line[i] = ft_toupper(line[i]);
	i = 0;
	if (ft_strlen(line) == 0)
		ft_error_file();
	while ((line[i] >= '0' && line[i] <= '9')
			|| (line[i] >= 'A' && line[i] <= 'F'))
	{
		add = line[i] > '9' ? 9 + line[i] - 'A' + 1 : line[i] - '0';
		nbr = nbr * 16 + add;
		i++;
	}
	if (nbr > 0xFFFFFF)
	{
		ft_putendl("error: color value must be between 0x000000 and 0xFFFFFF");
		exit(0);
	}
	return (nbr);
}

double	atoi_double(char *line)
{
	double	ent;
	double	dec;
	double	sign;

	sign = 1.0;
	ent = (double)ft_atoi(line);
	if (ft_strchr(line, '-'))
	{
		sign = -1.0;
		ent = -ent;
	}
	line = ft_strchr(line, '.') != NULL ? ft_strchr(line, '.') + 1 : NULL;
	if (!line)
		ft_error_file();
	dec = (double)ft_atoi(line);
	while (dec >= 1.0)
		dec = dec / 10.0;
	ent = sign * (dec + ent);
	if (ent != ent)
		ft_error_file();
	return (ent);
}

t_vec	intersection(void *obj, t_vec ray, t_vec org)
{
	t_vec	inter;
	double	t;

	t = *(double*)(obj);
	inter.x = org.x + ray.x * t;
	inter.y = org.y + ray.y * t;
	inter.z = org.z + ray.z * t;
	return (inter);
}
