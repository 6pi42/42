/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 10:41:22 by cboyer            #+#    #+#             */
/*   Updated: 2016/01/18 18:00:53 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_type(char type, va_list args)
{
	if (type == 'd' || type == 'i'		)
		ft_putstr(ft_itoa_base(va_arg(args, long),10));
	if (type == 'x')
		ft_putstr(ft_itoa_base(va_arg(args, long), 16));
	if (type == 'X')
		ft_putstr(ft_itoa_base(va_arg(args, long), 16));
	if (type == 'o')
		ft_putstr(ft_itoa_base(va_arg(args, long), 8));
	return (0);
}


static char	is_argc(char c)
{
	if (c == 'u' || c == 's' || c == 'd' || c == 'x' || c == 'X' || c == 'c'
	|| c == 'S' || c == 'i' || c == 'p' || c == 'U' || c == 'D' || c == 'o' ||
	c == 'C')
		return (c);
	return (0);
}

int	ft_print(const char *str, int index)
{
	int	i;
	int	ok;

	ok = str[index] == '%' ? 1 : 0;
	i = index;
	while (str[i] && str[i] != '%')
	{
		ft_putcharwchart(str[i]);
		i++;
		ok = 1;
	}
	return (ok != 0 ? i : -1);
}

char	*get_argc_flags(const char *str, int i)
{
	char	*argc;
	int			index;

	index = i + 1;
	while (str[index] && str[index] != ' ' && !is_argc(str[index]))
		index++;
	if (!is_argc(str[index]))
		ft_error();
	argc = malloc(sizeof(char) * (index - i + 1));
	argc = ft_strncpy(argc, str + index, index - i);
	return (argc);
}

int		ft_printf(const char *format, ...)
{
	int		i;
	int		argc;
	va_list	ap;
	char	*flags;

	va_start(ap, format);

	argc = 0;
	i = 0;
	while ((i = ft_print(format, i)) != -1)
	{
		flags = get_argc_flags(format, i);
		i += ft_strlen(flags);
		printf("argc : %s\n", flags);
	}
	return (1);
}

int main()
{
	ft_printf("dwhduwhduwhd %d vdh");
	return 0;
}
