/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:44:00 by abin-saa          #+#    #+#             */
/*   Updated: 2022/06/02 12:29:30 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countdigt(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	unsigned int	number;
	char			*str;
	size_t			len;

	len = countdigt(n);
	number = n;
	if (n < 0)
	{
		number = -1 * n;
		len++;
	}
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	if (number == 0)
		str[--len] = '0';
	while (number)
	{
		str[--len] = number % 10 + '0';
		number = number / 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
// #include <stido.h
// int	main()
// {
// 	char * str = ft_itoa(0);
// 	printf("%s", str);
// }