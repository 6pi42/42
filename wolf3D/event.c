/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 11:54:41 by cboyer            #+#    #+#             */
/*   Updated: 2016/01/27 11:55:40 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	key_hook(int keycode, t_map *map)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(map->e.mlx, map->e.win);
		exit(0);
	}
	return (1);
}

