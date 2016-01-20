/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 17:11:50 by cboyer            #+#    #+#             */
/*   Updated: 2015/12/10 17:11:51 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char	*destptr;
	char	*srcptr;
	size_t	i;

	i = 0;
	destptr = (char*)dest;
	srcptr = (char*)src;
	while (i < n)
	{
		destptr[i] = srcptr[i];
		if (srcptr[i] == c)
			return ((char*)&destptr[i] + 1);
		i++;
	}
	return (NULL);
}
