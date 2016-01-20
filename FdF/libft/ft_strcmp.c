/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 17:14:01 by cboyer            #+#    #+#             */
/*   Updated: 2015/12/10 17:14:02 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *str1, const char *str2)
{
	int				i;
	unsigned char	*tmp1;
	unsigned char	*tmp2;

	i = 0;
	tmp1 = (unsigned char*)str1;
	tmp2 = (unsigned char*)str2;
	while (tmp1[i] == tmp2[i] && tmp1[i] != '\0' && tmp2[i] != '\0')
		i++;
	return (tmp1[i] - tmp2[i]);
}
