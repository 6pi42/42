/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 17:15:01 by cboyer            #+#    #+#             */
/*   Updated: 2015/12/10 17:15:02 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*tmpdest;
	const char	*tmpsrc;
	size_t		n;
	size_t		destlen;

	n = size;
	tmpdest = dst;
	tmpsrc = src;
	while (n-- != 0 && *tmpdest != '\0')
		tmpdest++;
	destlen = tmpdest - dst;
	n = size - destlen;
	if (n == 0)
		return (destlen + ft_strlen(tmpsrc));
	while (*tmpsrc != '\0')
	{
		if (n != 1)
		{
			*tmpdest++ = *tmpsrc;
			n--;
		}
		tmpsrc++;
	}
	*tmpdest = '\0';
	return (destlen + (tmpsrc - src));
}
