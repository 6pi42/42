/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 17:16:52 by cboyer            #+#    #+#             */
/*   Updated: 2015/12/10 17:16:53 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s)
{
	size_t	j;
	size_t	i;
	size_t	k;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	j = 0;
	k = 0;
	while (s[j])
	{
		if (s[j] != ' ' && s[j] != '\t' && s[j] != '\n')
		{
			j++;
			k = j;
		}
		else
			j++;
	}
	if (s && k == 0)
		return (ft_strdup(""));
	return (ft_strsub(s, i, (k - i)));
}
