/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 13:59:34 by cboyer            #+#    #+#             */
/*   Updated: 2016/01/14 15:17:23 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		containeof(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static char		*ft_strjoinnfree(char *tmp, char *buf, int n)
{
	char	*str;

	str = NULL;
	if (n == -1)
		n = BUFF_SIZE;
	if (!tmp)
	{
		if (!(str = (char*)malloc(sizeof(char) * n + 1)))
			return (NULL);
	}
	else
	{
		if (!(str = (char*)malloc(sizeof(char) * (n + ft_strlen(tmp)) + 1)))
			return (NULL);
	}
	str[0] = '\0';
	if (tmp)
	{
		str = ft_strcpy(str, tmp);
		free(tmp);
		tmp = NULL;
	}
	ft_strncat(str, buf, n);
	return (str);
}

static void		move_buf(char *buf, int n)
{
	char	tmp[BUFF_SIZE];
	int		i;

	i = 0;
	ft_bzero((void*)tmp, BUFF_SIZE);
	while (buf[i + n])
	{
		tmp[i] = buf[i + n];
		i++;
	}
	i = 0;
	ft_bzero((void*)buf, BUFF_SIZE);
	while (tmp[i])
	{
		buf[i] = tmp[i];
		i++;
	}
}

int				get_next_line(int const fd, char **line)
{
	static t_buf	sbuf;
	char			*tmp;
	int				end;

	tmp = NULL;
	while (1)
	{
		if (!ft_strlen(sbuf.buf))
		{
			if ((sbuf.ret = read(fd, sbuf.buf, BUFF_SIZE)) == -1)
				return (-1);
			sbuf.buf[BUFF_SIZE] = '\0';
			if (!sbuf.ret)
				break ;
		}
		if (!(tmp = ft_strjoinnfree(tmp, sbuf.buf, containeof(sbuf.buf))))
			return (-1);
		end = containeof(sbuf.buf) == -1 ? 0 : 1;
		move_buf(sbuf.buf, end == 1 ? containeof(sbuf.buf) + 1 : BUFF_SIZE);
		if (end)
			break ;
	}
	return ((*line = tmp) && sbuf.ret != 0);
}
