/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 10:30:03 by abin-saa          #+#    #+#             */
/*   Updated: 2022/05/17 15:52:15 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*x1;
	unsigned char	*x2;

	i = 0;
	x1 = (unsigned char *)s1;
	x2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (n--)
	{
		if (x1[i] != x2[i])
			return (x1[i] - x2[i]);
			i++;
	}
	return (0);
}
