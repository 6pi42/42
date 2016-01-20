/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 10:41:32 by cboyer            #+#    #+#             */
/*   Updated: 2016/01/18 11:37:06 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/includes/libft.h"
# include <stdarg.h>
#include <stdio.h>

int		ft_printf(const char *format, ...);
char	*ft_itoa_base(int n, int base);
void	ft_putcharwchart(wchar_t c);
void	ft_error(void);

#endif
