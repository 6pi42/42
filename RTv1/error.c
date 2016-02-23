/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 18:21:02 by cboyer            #+#    #+#             */
/*   Updated: 2016/02/23 13:27:30 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_error(void)
{
	ft_putendl("error");
	exit(0);
}

void	ft_error_file(void)
{
	ft_putendl("error: file not well formatted or invalid");
	exit(0);
}

void	ft_error_malloc(void)
{
	ft_putendl("error: memory can not be allocated");
	exit(0);
}

void	ft_error_mlx(void)
{
	ft_putendl("error: mlx can not be initialized");
	exit(0);
}

void	ft_error_arg(void)
{
	ft_putendl("error: invalid argument. use: ./retv1 <scene_name>");
	exit(0);
}
