/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 15:02:16 by cboyer            #+#    #+#             */
/*   Updated: 2016/01/18 15:27:31 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_intlen_base(int n, int base)
{
	int i;

	i = 1;
	if (n < 0 && base == 10)
		i++;
	while (n > (base - 1) || (n < -9 && base == 10))
	{
		i++;
		n = n / base;
	}
	return (i);
}

char	*ft_itoa_base(int n, int base)
{
	char	*tmp;
	int		ntmp;
	int		len;
	int		i;

	len = ft_intlen_base(n, base);
	if ((tmp = malloc(sizeof(char) * len + 1)) == NULL)
		return (NULL);
	if (n < 0 && base == 10)
		tmp[0] = '-';
	i = len - 1;
	tmp[len] = '\0';
	while (n != 0)
	{
		ntmp = n > 0 ? (n % base) : -(n % base);
		tmp[i] = ntmp > 9 ? ((ntmp - 10) + 'A') : (ntmp + '0');
		i--;
		n = n / base;
	}
	return (tmp);
}
