/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 14:38:50 by cboyer            #+#    #+#             */
/*   Updated: 2015/12/09 18:32:36 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	ft_isingrid(t_grid grid, t_tetra tetra, t_pos pos)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (pos.y + tetra.pos[i].x < 0 || pos.y + tetra.pos[i].x >= grid.size)
			return (0);
		if (pos.x + tetra.pos[i].y < 0 || pos.x + tetra.pos[i].y >= grid.size)
			return (0);
		i++;
	}
	return (1);
}

static int	ft_isvalid(t_grid grid, t_tetra tetra, t_pos pos)
{
	int	i;

	i = 0;
	if (!ft_isingrid(grid, tetra, pos))
		return (0);
	while (i < 4)
	{
		if (grid.grid[pos.y + tetra.pos[i].x][pos.x + tetra.pos[i].y] != -1)
			return (0);
		i++;
	}
	return (1);
}

void		ft_putingrid(t_grid grid, t_tetra tetra, t_pos pos)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		grid.grid[pos.y + tetra.pos[i].x][pos.x + tetra.pos[i].y] = tetra.index;
		i++;
	}
}

void		ft_removetetra(t_grid grid, t_tetra tetra, t_pos pos)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		grid.grid[pos.y + tetra.pos[i].x][pos.x + tetra.pos[i].y] = -1;
		i++;
	}
}

int			ft_nextvalid(t_grid grid, t_tetra tetra, t_pos *pos)
{
	if (pos->y == grid.size + 1)
		return (0);
	if (ft_isvalid(grid, tetra, *pos))
		return (1);
	increment(grid, pos);
	return (ft_nextvalid(grid, tetra, pos));
}
