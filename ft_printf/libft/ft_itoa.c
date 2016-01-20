/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 17:10:53 by cboyer            #+#    #+#             */
/*   Updated: 2015/12/10 17:10:54 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lenint(int c)
{
	int	nb;

	nb = 1;
	if (c >= -9 && c <= 9)
		return (1);
	while (c > 9 || c < -9)
	{
		nb++;
		c = c / 10;
	}
	return (nb);
}

char		*ft_itoa(int n)
{
	char			*nbr;
	int				len;
	long int		tmp;
	int				i;

	tmp = (long int)n;
	len = (tmp < 0 ? 1 : 0) + ft_lenint(tmp);
	if ((nbr = (char*)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	if (tmp < 0)
	{
		nbr[0] = '-';
		tmp = -tmp;
	}
	i = len - 1;
	nbr[len] = '\0';
	while (len >= 0 && (n < 0 ? i > 0 : i >= 0))
	{
		nbr[i] = (tmp % 10) + '0';
		tmp = tmp / 10;
		i--;
	}
	return (nbr);
}
