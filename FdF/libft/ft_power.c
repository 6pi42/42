/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 17:12:37 by cboyer            #+#    #+#             */
/*   Updated: 2015/12/10 17:12:38 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_power(int nb, unsigned int exp)
{
	int tmp;

	if (exp == 0)
		return (1);
	tmp = ft_power(nb, exp / 2);
	if ((exp % 2) == 0)
		return (tmp * tmp);
	else
		return (nb * tmp * tmp);
}
