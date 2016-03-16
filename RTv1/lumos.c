/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lumos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 14:56:20 by cboyer            #+#    #+#             */
/*   Updated: 2016/03/16 15:59:25 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int     moyenne(int *n, int len)
{
    int nb;
    int i;

    if (len == 0)
        return (0);
    i = 0;
    nb = 0;
    while (i < len)
    {
        nb += n[i];
        i++;
    }
    nb /= len;
    return (nb);
}

int	moy_rgb(int *rgb, int len)
{
	int	red[len];
	int	green[len];
	int	blue[len];
    int i;

    i = 0;
    while (i < len)
    {
        red[i] = (rgb[i] & 0xFF0000) >> 16;
	    green[i] = (rgb[i] & 0xFF00) >> 8;
	    blue[i] = rgb[i] & 0xFF;
        i++;
    }
    red[0] = moyenne(red, len);
    blue[0] = moyenne(blue, len);
    green[0] = moyenne(green, len);
    red[0] = red[0] > 255 ? 255 : red[0];
	blue[0] = blue[0] > 255 ? 255 : blue[0];
	green[0] = green[0] > 255 ? 255 : green[0];
	i = red[0] << 16 | green[0] << 8 | blue[0];
	return (i);
}

int     multi_spot(void **st, void *small, t_vec ray, t_map *map)
{
    int rgb[map->tab->nb_spot];
    int i;
    int tmp;
    t_vec   inter;

    i = 0;
    while (i < map->tab->nb_spot)
    {
        if (small == st[0])
            tmp = sphere_lumos(map, small, ray, map->tab->spot[i]);
        else if (small == st[2])
            tmp = cyl_lumos(map, small, ray, map->tab->spot[i]);
        else if (small == st[3])
            tmp = cone_lumos(map, small, ray, map->tab->spot[i]);
        //else if (small == st[1])
        //    tmp = plan_lumos(map, small, ray, map->tab->spot[i]);
        inter = intersection(small, ray, map->tab->cam.pos);
        if (!(shadow(map, small, sous_vec(map->tab->spot[i], inter), map->tab->spot[i])))
            tmp = get_shadow(map, small, inter, map->tab->spot[i]);
        rgb[i] = tmp;
        i++;
    }
    tmp = moy_rgb(rgb, map->tab->nb_spot);
    return (tmp);
}
