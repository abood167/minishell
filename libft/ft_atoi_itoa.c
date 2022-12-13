/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_itoa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbokhari <sbokhari@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 21:44:21 by sbokhari          #+#    #+#             */
/*   Updated: 2022/07/17 16:05:55 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	overflowcheck(long long val, int sign, char c)
{
	if (sign == 1)
	{
		if (val > __LONG_MAX__ / 10 || (val == __LONG_MAX__ / 10 && c
				- '0' > __LONG_MAX__ % 10))
			return (-1);
	}
	else
	{
		if (-val < -(__LONG_MAX__ - 1) / 10 || (-val == -(__LONG_MAX__ - 1) / 10
				&& c - '0' > __LONG_MAX__ % 10))
			return (0);
	}
	return (1);
}

int	ft_atoi(char const *str)
{
	long long	val;
	int			sign;
	int			i;

	val = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (overflowcheck(val, sign, str[i]) != 1)
			return (overflowcheck(val, sign, str[i]));
		val *= 10;
		val += str[i++] - '0';
	}
	return ((int)val * sign);
}

//itoa

static int	numlen(int n)
{
	int	len;

	len = 1;
	while (n / 10 != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	val;
	int		len;
	char	*numchar;

	val = (long)n;
	len = numlen(n);
	if (n < 0)
		len++;
	numchar = (char *)malloc(sizeof(char) * (len + 1));
	if (!numchar)
		return (NULL);
	numchar[len] = '\0';
	if (val < 0)
	{
		numchar[0] = '-';
		val *= -1;
	}
	numchar[--len] = val % 10 + '0';
	val /= 10;
	while (val != 0)
	{
		numchar[--len] = val % 10 + '0';
		val /= 10;
	}
	return (numchar);
}
