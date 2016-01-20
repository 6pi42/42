/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 17:16:15 by cboyer            #+#    #+#             */
/*   Updated: 2015/12/10 17:16:16 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	str = malloc(sizeof(char) * size + 1);
	if (str)
	{
		while (i <= size)
		{
			str[i] = '\0';
			i++;
		}
	}
	return (str);
}
