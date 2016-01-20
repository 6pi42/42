/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_grid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 14:27:35 by cboyer            #+#    #+#             */
/*   Updated: 2015/12/08 13:26:24 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	ft_printgrid(char **grid, int size)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (grid[i][j] == -1)
				ft_putchar('.');
			else
				ft_putchar('A' + grid[i][j]);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}

void	ft_freegrid(char **grid, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

char	**ft_initgrid(int size)
{
	int		i;
	int		j;
	char	**grid;

	i = 0;
	if (!(grid = (char**)malloc(sizeof(char*) * size)))
		return (NULL);
	while (i < size)
	{
		if (!(grid[i] = (char*)malloc(sizeof(char) * size)))
			return (NULL);
		j = 0;
		while (j < size)
		{
			grid[i][j] = -1;
			j++;
		}
		i++;
	}
	return (grid);
}
