/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:08:21 by abin-saa          #+#    #+#             */
/*   Updated: 2022/05/21 11:51:01 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n <= 2147483647 && n >= -2147483648)
	{
		if (n < 0)
		{
			if (n == -2147483648)
				return (ft_putstr_fd("-2147483648", fd));
			ft_putchar_fd('-', fd);
			n = n * -1;
		}
		if (n <= 9)
			ft_putchar_fd(n + '0', fd);
		if (n > 9)
		{
			ft_putnbr_fd(n / 10, fd);
			ft_putnbr_fd(n % 10, fd);
		}
	}
}
