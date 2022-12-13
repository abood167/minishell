/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbokhari <sbokhari@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 18:10:08 by sbokhari          #+#    #+#             */
/*   Updated: 2022/07/22 15:42:23 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_zeroinit_plist(t_plist *p)
{
	p->padlen = 0;
	p->padzero = 0;
	p->preclen = -1;
	p->postpad = 0;
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	char	*str;
	int		count;
	t_plist	p;

	ft_zeroinit_plist(&p);
	va_start(args, s);
	str = (char *)s;
	count = 0;
	while (*str)
	{
		if (*str != '%')
			count += ft_putchar_printf(*str, p);
		else
			count += ft_printf_puttype(&str, &args, p);
		str++;
	}
	va_end(args);
	return (count);
}
