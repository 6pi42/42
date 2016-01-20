/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 17:14:55 by cboyer            #+#    #+#             */
/*   Updated: 2015/12/10 17:14:56 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*tmp;
	int		i;

	i = 0;
	if (s1 && s2)
	{
		tmp = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1);
		if (tmp == NULL)
			return (NULL);
		while (s1[i])
		{
			tmp[i] = s1[i];
			i++;
		}
		while (*s2)
		{
			tmp[i] = *s2;
			i++;
			s2++;
		}
		tmp[i] = '\0';
		return (tmp);
	}
	return (NULL);
}
