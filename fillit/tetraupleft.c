/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetraupleft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 10:44:51 by cboyer            #+#    #+#             */
/*   Updated: 2015/12/09 18:32:54 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	go_upleft(t_tetra *tab)
{
	int	i;
	int	j;

	i = 0;
	while (i < get_nb_tetraminos(tab))
	{
		j = -1;
		while (tab[i].pos[0].x > 0)
		{
			while (++j < 4)
				tab[i].pos[j].x--;
			j = -1;
		}
		while (tab[i].pos[0].y > 0)
		{
			while (++j < 4)
				tab[i].pos[j].y--;
			j = -1;
		}
		i++;
	}
}
