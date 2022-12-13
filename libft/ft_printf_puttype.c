/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_puttype.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbokhari <sbokhari@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 18:10:11 by sbokhari          #+#    #+#             */
/*   Updated: 2022/07/22 15:42:58 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_printf_padprec(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else if (c == '.')
		return (1);
	else if (c == '-')
		return (1);
	return (0);
}

int	ft_printf_puttype(char **str, va_list *args, t_plist p)
{
	(*str)++;
	if (**str == 'c')
		return (ft_putchar_printf((char)va_arg(*args, int), p));
	else if (**str == 's')
		return (ft_putstr_printf(va_arg(*args, char *), p));
	else if (**str == 'p')
		return (ft_putaddress_printf(va_arg(*args, void *), 1, p));
	else if (**str == 'd' || **str == 'i')
		return (ft_putnbr_printf(va_arg(*args, int), p));
	else if (**str == 'u')
		return (ft_putunbr_printf(va_arg(*args, unsigned int), p));
	else if (**str == 'x')
		return (ft_puthex_printf(va_arg(*args, unsigned int), 0, p));
	else if (**str == 'X')
		return (ft_puthex_printf(va_arg(*args, unsigned int), 1, p));
	else if (**str == '%')
		return (write(1, "%", 1));
	else if (ft_printf_padprec(**str))
		return (ft_putpadding_printf(str, args, p));
	else if (**str == '#' || **str == '+' || **str == ' ')
		return (ft_putformatting_printf(str, args, p));
	return (0);
}
