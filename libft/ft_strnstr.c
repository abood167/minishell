/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:55:11 by abin-saa          #+#    #+#             */
/*   Updated: 2022/06/02 13:20:32 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *h, const char *n, size_t len)
{
	size_t	a;
	size_t	b;
	char	*m;

	m = (char *)h;
	a = 0;
	if (!*n)
		return ((char *)h);
	while (h[a] != '\0' && a < len)
	{
		b = 0;
		while (h[a + b] == n[b] && n[b] != '\0' && a + b < len)
		{
			b++;
		}
		if (b == ft_strlen(n))
			return (&m[a]);
		a++;
	}
	return (NULL);
}
