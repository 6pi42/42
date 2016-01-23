/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 17:12:24 by cboyer            #+#    #+#             */
/*   Updated: 2015/12/10 17:12:25 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*str_dest;
	unsigned char	*str_src;
	size_t			i;

	i = 0;
	str_dest = ((unsigned char *)dest);
	str_src = ((unsigned char *)src);
	if (str_dest > str_src)
	{
		while (i < n)
		{
			str_dest[n - 1] = str_src[n - 1];
			n--;
		}
		return (dest);
	}
	else
		while (i < n)
		{
			str_dest[i] = str_src[i];
			i++;
		}
	return (dest);
}
