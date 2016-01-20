/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 17:12:12 by cboyer            #+#    #+#             */
/*   Updated: 2015/12/10 17:12:13 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char *destptr;
	char *srcptr;

	destptr = dest;
	srcptr = (char*)src;
	while (n > 0)
	{
		*destptr++ = *srcptr++;
		n--;
	}
	return (dest);
}
