/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/23 15:51:24 by cboyer            #+#    #+#             */
/*   Updated: 2016/01/23 15:52:42 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		ft_error(void)
{
	ft_putstr("error\n");
	exit(0);
}

void		ft_print_choices(void)
{
	ft_putstr("-mandelbrot\n-julia\n-sierpinski\n");
	exit(0);
}
