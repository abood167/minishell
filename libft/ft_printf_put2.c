/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_put2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbokhari <sbokhari@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 18:10:11 by sbokhari          #+#    #+#             */
/*   Updated: 2022/07/22 15:42:56 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int	ft_puthex_printf(long long nb, int caps, t_plist p)
{
	int	count;

	if (!p.preclen && !nb)
		return (0);
	count = 0;
	if (nb < 0)
	{
		if (!p.padzero)
			count += write(1, "-", 1);
		if (nb == -__LONG_LONG_MAX__ - 1)
		{
			count += ft_puthex_printf(-(nb / 16), caps, p);
			nb = -(nb % 16);
		}
		else
			nb *= -1;
	}
	if (nb >= 16)
		count += ft_puthex_printf(nb / 16, caps, p);
	if (caps)
		count += write(1, &"0123456789ABCDEF"[nb % 16], 1);
	else
		count += write(1, &"0123456789abcdef"[nb % 16], 1);
	return (count);
}

int	ft_putaddress_printf(void *addr, int first, t_plist p)
{
	int					count;
	unsigned long long	nb;

	if (!p.preclen && !addr)
		return (0);
	count = 0;
	nb = (unsigned long long)addr;
	if (first && !p.padzero)
		count += write(1, "0x", 2);
	if (nb >= 16)
		count += ft_putaddress_printf((void *)(nb / 16), 0, p);
	count += write(1, &"0123456789abcdef"[(nb % 16)], 1);
	return (count);
}
