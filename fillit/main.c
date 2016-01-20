/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 14:11:01 by cboyer            #+#    #+#             */
/*   Updated: 2015/12/16 14:56:07 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	get_nb_tetraminos(t_tetra *tab)
{
	int	i;

	i = 0;
	while (tab[i].pos[0].x != -1)
		i++;
	return (i);
}

int	main(int argc, char *argv[])
{
	t_tetra	*tab;
	t_grid	*structgrid;

	if (!(structgrid = malloc(sizeof(t_grid))))
		return (0);
	if (!(tab = malloc(sizeof(t_tetra) * 27)))
		return (0);
	if (!(check_map(argv[1], tab)) || argc != 2 || !get_nb_tetraminos(tab))
	{
		ft_putstr("error\n");
		return (0);
	}
	go_upleft(tab);
	structgrid->grid = ft_initgrid(2);
	ft_solve(tab);
	free(tab);
	free(structgrid);
	return (0);
}
