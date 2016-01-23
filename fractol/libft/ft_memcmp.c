/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 17:12:04 by cboyer            #+#    #+#             */
/*   Updated: 2015/12/10 17:12:05 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1ptr;
	unsigned char	*s2ptr;
	size_t			i;

	s1ptr = (unsigned char*)s1;
	s2ptr = (unsigned char*)s2;
	i = 0;
	while (i < n)
	{
		if (s1ptr[i] != s2ptr[i])
			return ((s1ptr[i]) - (s2ptr[i]));
		i++;
	}
	return (0);
}
