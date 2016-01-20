/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 14:11:46 by cboyer            #+#    #+#             */
/*   Updated: 2015/12/09 18:32:37 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include "libft.h"
# include <fcntl.h>

typedef struct				s_pos
{
	char					x;
	char					y;
}							t_pos;

typedef struct				s_tetra
{
	t_pos					pos[4];
	char					index;
}							t_tetra;

typedef struct				s_grid
{
	char					**grid;
	int						size;
}							t_grid;

void						*check_map(const char *map, t_tetra *tab);
int							check_tetra(t_tetra tetra);
void						go_upleft(t_tetra *tab);
void						ft_printgrid(char **grid, int size);
void						ft_freegrid(char **grid, int size);
char						**ft_initgrid(int size);
int							get_nb_tetraminos(t_tetra *tab);
void						ft_solve(t_tetra *list);
int							ft_backtrack(t_grid grid, t_tetra *tetra);
void						ft_removetetra(t_grid grid, t_tetra tetra,
							t_pos pos);
int							ft_nextvalid(t_grid grid, t_tetra tetra,
							t_pos *pos);
void						ft_putingrid(t_grid grid, t_tetra tetra, t_pos pos);
int							ft_backtrack(t_grid grid, t_tetra *tetra);
void						ft_solve(t_tetra *list);
void						increment(t_grid grid, t_pos *pos);

#endif
