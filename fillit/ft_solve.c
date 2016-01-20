/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/05 13:38:52 by cboyer            #+#    #+#             */
/*   Updated: 2015/12/09 18:32:39 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	increment(t_grid grid, t_pos *pos)
{
	if (pos->x + 1 <= grid.size)
		pos->x++;
	else
	{
		pos->x = 0;
		pos->y++;
	}
}

int		ft_backtrack(t_grid grid, t_tetra *tetra)
{
	t_pos	pos;

	pos.x = 0;
	pos.y = 0;
	if (tetra->pos[0].x == -1)
		return (1);
	while (ft_nextvalid(grid, *tetra, &pos) != 0)
	{
		ft_putingrid(grid, *tetra, pos);
		if (ft_backtrack(grid, tetra + 1))
			return (1);
		ft_removetetra(grid, *tetra, pos);
		increment(grid, &pos);
	}
	return (0);
}

void	ft_solve(t_tetra *list)
{
	t_grid	grid;

	grid.size = 2;
	grid.grid = ft_initgrid(grid.size);
	if (grid.grid)
	{
		while (ft_backtrack(grid, &list[0]) == 0)
		{
			ft_freegrid(grid.grid, grid.size);
			grid.size++;
			grid.grid = ft_initgrid(grid.size);
		}
		ft_printgrid(grid.grid, grid.size);
		ft_freegrid(grid.grid, grid.size);
	}
}
