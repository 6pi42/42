/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 17:16:21 by cboyer            #+#    #+#             */
/*   Updated: 2015/12/10 17:16:22 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ismatch(const char *str1, const char *str2, size_t ad, size_t n)
{
	size_t count;

	count = 0;
	while (str2[count])
	{
		if (ad + count >= n)
			return (0);
		if (str1[count] != str2[count])
			return (0);
		if (str1[count] == '\0')
			return (0);
		count++;
	}
	return (1);
}

char			*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	int count;

	count = 0;
	if (ft_strlen(s2) == 0)
		return ((char*)s1);
	while (s1[count] && (size_t)count < n)
	{
		if (s1[count] == s2[0])
		{
			if (ismatch(&s1[count], s2, count, n))
				return ((char*)&s1[count]);
		}
		count++;
	}
	return (NULL);
}
