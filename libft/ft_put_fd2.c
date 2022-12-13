/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_fd2.c                                        :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: sbokhari <sbokhari@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:06:03 by sbokhari          #+#    #+#             */
/*   Updated: 2022/07/17 16:06:12 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_puthex_fd(long long nb, int fd, int caps)
{
	if (nb < 0)
	{
		write(fd, "-", 1);
		if (nb == -__LONG_LONG_MAX__ - 1)
		{
			ft_puthex_fd(nb / 16, fd, caps);
			nb = -(nb % 16);
		}
		else
			nb *= -1;
	}
	if (nb >= 16)
		ft_puthex_fd(nb / 16, fd, caps);
	if (caps)
		write(fd, &"0123456789ABCDEF"[nb % 16], 1);
	else
		write(fd, &"0123456789abcdef"[nb % 16], 1);
}

void	ft_putaddress_fd(void *nb, int fd)
{
	char			num[16];
	int				count;
	unsigned long	addr;

	addr = (unsigned long)nb;
	count = 15;
	while (addr > 0)
	{
		if (addr % 16 < 10)
			num[count--] = '0' + addr % 16;
		else
			num[count--] = 'a' + addr % 16 - 10;
		addr /= 16;
	}
	while (count >= 0)
	{
		num[count--] = '0';
	}
	write(fd, &num, 16);
}
