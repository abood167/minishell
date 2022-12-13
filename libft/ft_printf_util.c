/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbokhari <sbokhari@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:43:01 by sbokhari          #+#    #+#             */
/*   Updated: 2022/07/22 15:43:02 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_padding_printf(int padlen, int padzero)
{
	int	count;

	count = 0;
	if (padzero)
		while (padlen-- > 0)
			count += write(1, "0", 1);
	else
		while (padlen-- > 0)
			count += write(1, " ", 1);
	return (count);
}

static int	overflowcheck(long long val, char c)
{
	if (val > __LONG_MAX__ / 10 || (val == __LONG_MAX__ / 10 && c
			- '0' > __LONG_MAX__ % 10))
		return (-1);
	return (1);
}

int	ft_atoi_printf(char const *str)
{
	long long	val;
	int			i;

	val = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (overflowcheck(val, str[i]) != 1)
			return (overflowcheck(val, str[i]));
		val *= 10;
		val += str[i++] - '0';
	}
	return ((int)val);
}
