/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 11:31:11 by cboyer            #+#    #+#             */
/*   Updated: 2015/12/09 18:32:38 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

#define BUF_SIZE	21

static void		init_tab(t_tetra *tab)
{
	int		i;
	t_tetra	*tetra;

	i = 0;
	if (!(tetra = malloc(sizeof(tetra))))
		return ;
	tetra->pos[0].x = -1;
	while (i < 27)
	{
		tab[i] = *tetra;
		i++;
	}
	free(tetra);
}

static	int		add_tab(t_tetra *tab, t_tetra tetra)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tab[i].pos[0].x != -1)
		i++;
	if (i == 26)
		return (0);
	while (j < 4)
	{
		tab[i].pos[j].x = tetra.pos[j].x;
		tab[i].pos[j].y = tetra.pos[j].y;
		j++;
		tab[i].index = i;
	}
	return (1);
}

static int		get_near(t_tetra tetra)
{
	int	j;
	int	i;
	int	near;

	i = -1;
	near = 0;
	while ((j = -1) && ++i < 4)
	{
		while (++j < 4)
		{
			if (tetra.pos[i].y == tetra.pos[j].y)
			{
				near = tetra.pos[i].x == tetra.pos[j].x + 1 ? near + 1 : near;
				near = tetra.pos[i].x == tetra.pos[j].x - 1 ? near + 1 : near;
			}
			if (tetra.pos[i].x == tetra.pos[j].x)
			{
				near = tetra.pos[i].y == tetra.pos[j].y + 1 ? near + 1 : near;
				near = tetra.pos[i].y == tetra.pos[j].y - 1 ? near + 1 : near;
			}
		}
	}
	return (near >= 6 ? near : 0);
}

static int		check_template(const char *str, t_tetra tetra, t_tetra *tab)
{
	int	bloc;
	int	i;

	i = 0;
	bloc = 0;
	while (str[i])
	{
		if (str[i] != '.' && str[i] != '#' && str[i] != '\n')
			return (0);
		if (str[i] == '\n' && (i % 5 != 4 && i != 20))
			return (0);
		if (str[i] == '#')
		{
			bloc++;
			if (bloc > 4)
				return (0);
			tetra.pos[bloc - 1].y = i % 5;
			tetra.pos[bloc - 1].x = i / 5;
		}
		i++;
	}
	if (!(get_near(tetra)))
		return (0);
	return (add_tab(tab, tetra));
}

void			*check_map(const char *map, t_tetra *tab)
{
	char		buf[BUF_SIZE + 1];
	int			fd;
	int			ret;
	t_tetra		*tetra;

	init_tab(tab);
	tetra = malloc(sizeof(t_tetra));
	if (!(fd = open(map, O_RDONLY)))
		return (NULL);
	while ((ret = read(fd, buf, BUF_SIZE)))
	{
		buf[ret] = '\0';
		if (!check_template(buf, *tetra, tab))
			return (NULL);
	}
	free(tetra);
	return (tab);
}
