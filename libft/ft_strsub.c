/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 17:16:46 by cboyer            #+#    #+#             */
/*   Updated: 2015/12/10 17:16:47 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(const char *s, unsigned int start, size_t len)
{
	char *str;

	if (s)
	{
		str = malloc(sizeof(char) * (len + 1));
		if (str == NULL)
			return (NULL);
		if (str)
		{
			while (start--)
				s++;
			ft_strncpy(str, s, len);
			str[len] = '\0';
		}
		return (str);
	}
	return (NULL);
}
