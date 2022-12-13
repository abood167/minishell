/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_put3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbokhari <sbokhari@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:42:18 by sbokhari          #+#    #+#             */
/*   Updated: 2022/07/22 15:42:57 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_preczeropad_printf(char c, int printlen, va_list *args,
		t_plist p)
{
	int	count;
	int	negflag;

	negflag = 0;
	count = 0;
	if ((c == 'd' || c == 'i' || c == 'u' || c == 'x' || c == 'X')
		&& p.preclen >= 0)
	{
		if ((c == 'd' || c == 'i') && va_arg(*args, int) < 0 && p.preclen >= 0)
			negflag = 1;
		if (printlen > p.preclen)
			count += ft_padding_printf(p.padlen - negflag - printlen, 0);
		else
			count += ft_padding_printf(p.padlen - negflag - p.preclen, 0);
		if (negflag)
			count += write(1, "-", 1);
		count += ft_padding_printf(p.preclen - printlen, 1);
	}
	else if ((c == 'c' || c == 's') || p.preclen <= 0)
	{
		p.padlen -= printlen;
		count += ft_padding_printf(p.padlen, p.padzero);
	}
	return (count);
}

static int	ft_getprintlen_printf(char **str, va_list *args, t_plist p)
{
	int		count;
	va_list	arg2;

	(*str)++;
	va_copy(arg2, *args);
	count = 0;
	if (**str == 'c')
		count += 1;
	else if (**str == 's')
		count += ft_countstr_printf(va_arg(*args, char *), p);
	else if (**str == 'p')
		count += ft_countaddress_printf(va_arg(*args, void *), 1, p);
	else if (**str == 'd' || **str == 'i')
		count += ft_countnbr_printf(va_arg(*args, int), p);
	else if (**str == 'u')
		count += ft_countunbr_printf(va_arg(*args, unsigned int), p);
	else if (**str == 'x')
		count += ft_counthex_printf(va_arg(*args, unsigned int), p);
	else if (**str == 'X')
		count += ft_counthex_printf(va_arg(*args, unsigned int), p);
	else if (**str == '%')
		count = 1;
	count += ft_preczeropad_printf(**str, count, &arg2, p);
	va_end(arg2);
	return (count);
}

static void	ft_init_plist(char **str, t_plist *p)
{
	int	flag;

	flag = 1;
	while (flag)
	{
		if (**str >= '0' && **str <= '9')
		{
			p->padlen = ft_atoi_printf(*str);
			if (**str == '0')
				p->padzero = 1;
		}
		else if (**str == '.')
			p->preclen = ft_atoi_printf(++(*str));
		else if (**str == '-')
		{
			p->padlen = 0;
			if (ft_atoi_printf(++(*str)))
				p->postpad = ft_atoi_printf(*str);
		}
		else
			flag = 0;
		while (**str >= '0' && **str <= '9')
			(*str)++;
	}
	(*str)--;
}

int	ft_putpadding_printf(char **str, va_list *args, t_plist p)
{
	int		printlen;
	int		count;
	va_list	args2;

	ft_init_plist(str, &p);
	va_copy(args2, *args);
	printlen = ft_getprintlen_printf(str, &args2, p);
	va_end(args2);
	(*str)--;
	count = printlen;
	ft_printf_puttype(str, args, p);
	p.postpad -= count;
	count += ft_padding_printf(p.postpad, 0);
	return (count);
}
