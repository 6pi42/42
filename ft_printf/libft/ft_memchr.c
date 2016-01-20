/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 17:11:58 by cboyer            #+#    #+#             */
/*   Updated: 2015/12/10 17:11:59 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*sptr;
	size_t	i;

	i = 0;
	sptr = (char*)s;
	while (i < n)
	{
		if (sptr[i] == (char)c)
			return (&sptr[i]);
		i++;
	}
	return (NULL);
}
