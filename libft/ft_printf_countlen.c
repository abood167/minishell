/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_count1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbokhari <sbokhari@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:42:16 by sbokhari          #+#    #+#             */
/*   Updated: 2022/07/22 15:42:24 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_countnbr_printf(int n, t_plist p)
{
	long	nb;
	int		count;

	if (!p.preclen && !n)
		return (0);
	nb = (long)n;
	count = 1;
	if (nb < 0)
	{
		if (p.padzero && p.preclen < 0)
			write(1, "-", 1);
		if (p.preclen < 0)
			count++;
		nb *= -1;
	}
	if (nb >= 10)
		count += ft_countnbr_printf((int)(nb / 10), p);
	return (count);
}

int	ft_countunbr_printf(unsigned int n, t_plist p)
{
	int	count;

	if (!p.preclen && !n)
		return (0);
	count = 1;
	if (n >= 10)
		count += ft_countunbr_printf((int)(n / 10), p);
	return (count);
}

int	ft_countstr_printf(char *s, t_plist p)
{
	int	count;

	if (!s)
		s = "(null)";
	count = ft_strlen(s);
	if (p.preclen >= 0 && p.preclen < count)
		count = p.preclen;
	return (count);
}

int	ft_counthex_printf(long long nb, t_plist p)
{
	int	count;

	if (!p.preclen && !nb)
		return (0);
	count = 1;
	if (nb < 0)
	{
		if (p.padzero || p.preclen >= 0)
			write(1, "-", 1);
		if (p.preclen < 0)
			count++;
		if (nb == -__LONG_LONG_MAX__ - 1)
		{
			count += ft_counthex_printf(-(nb / 16), p);
			nb = -(nb % 16);
		}
		else
			nb *= -1;
	}
	if (nb >= 16)
		count += ft_counthex_printf(nb / 16, p);
	return (count);
}

int	ft_countaddress_printf(void *addr, int first, t_plist p)
{
	int					count;
	unsigned long long	nb;

	if (!p.preclen && !addr)
		return (0);
	count = 1;
	nb = (unsigned long long)addr;
	if (first)
	{
		count += 2;
		if (p.padzero)
			write(1, "0x", 2);
	}
	if (nb >= 16)
		count += ft_countaddress_printf((void *)(nb / 16), 0, p);
	return (count);
}
