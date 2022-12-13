/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbokhari <sbokhari@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 21:46:19 by sbokhari          #+#    #+#             */
/*   Updated: 2022/07/17 16:06:12 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*a;
	unsigned char	chr;
	size_t			i;

	i = 0;
	a = (unsigned char *)s;
	chr = (unsigned char)c;
	while (n && i < n - 1)
	{
		if (a[i] == chr)
			return (&a[i]);
		i++;
	}
	if (a[i] == chr && n)
		return (&a[i]);
	return (NULL);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*a;

	i = 0;
	dest = dst;
	if (dst || src)
	{
		a = (unsigned char *)src;
		while (i < n)
		{
			dest[i] = a[i];
			i++;
		}
	}
	return (dest);
}

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*a;

	i = -1;
	dest = dst;
	a = (unsigned char *)src;
	if (dst || src)
	{
		if (dst <= src)
		{
			while (++i < n)
				dest[i] = a[i];
		}
		else
		{
			while (++i < n)
				dest[n - i - 1] = a[n - i - 1];
		}
	}
	return (dest);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*a1;
	unsigned char	*a2;
	size_t			i;

	a1 = (unsigned char *)s1;
	a2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	i = 0;
	while (i < n - 1 && a1[i] == a2[i])
	{
		i++;
	}
	return (a1[i] - a2[i]);
}
