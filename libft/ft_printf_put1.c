/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_put1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbokhari <sbokhari@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 18:10:10 by sbokhari          #+#    #+#             */
/*   Updated: 2022/07/22 15:42:25 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_printf(char c, t_plist p)
{
	(void)p;
	return (write(1, &c, 1));
}

int	ft_putnbr_printf(int n, t_plist p)
{
	long	nb;
	int		count;

	if (!p.preclen && !n)
		return (0);
	nb = (long)n;
	count = 0;
	if (nb < 0)
	{
		if (!p.padzero && p.preclen < 0)
			count += write(1, "-", 1);
		nb *= -1;
	}
	if (nb >= 10)
		count += ft_putnbr_printf((int)(nb / 10), p);
	count += write(1, &"0123456789"[nb % 10], 1);
	return (count);
}

int	ft_putunbr_printf(unsigned int n, t_plist p)
{
	int	count;

	if (!p.preclen && !n)
		return (0);
	count = 0;
	if (n >= 10)
		count += ft_putunbr_printf((int)(n / 10), p);
	count += write(1, &"0123456789"[n % 10], 1);
	return (count);
}

int	ft_putstr_printf(char *s, t_plist p)
{
	int	count;

	if (!s)
		s = "(null)";
	count = ft_strlen(s);
	if (p.preclen >= 0 && p.preclen < count)
		count = p.preclen;
	write(1, s, count);
	return (count);
}
