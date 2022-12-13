/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_put4.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbokhari <sbokhari@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:42:19 by sbokhari          #+#    #+#             */
/*   Updated: 2022/07/22 15:42:58 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putformatting2_printf(char **str, va_list *args, int *count)
{
	if (**str == '+')
	{
		while (**str == '+')
			(*str)++;
		(*str)--;
		if (va_arg(*args, int) >= 0)
			*count += write(1, "+", 1);
	}
	else if (**str == ' ')
	{
		while (**str == ' ')
			(*str)++;
		if ((**str == 'd' || **str == 'i') && va_arg(*args, int) >= 0)
			*count += write(1, " ", 1);
		(*str)--;
	}
}

int	ft_putformatting_printf(char **str, va_list *args, t_plist p)
{
	int		count;
	va_list	args2;

	count = 0;
	va_copy(args2, *args);
	if (**str == '#')
	{
		if (va_arg(args2, unsigned int))
		{
			if (*(*str + 1) == 'X')
				count += write(1, "0X", 2);
			else
				count += write(1, "0x", 2);
		}
	}
	else
		ft_putformatting2_printf(str, &args2, &count);
	va_end(args2);
	count += ft_printf_puttype(str, args, p);
	return (count);
}
