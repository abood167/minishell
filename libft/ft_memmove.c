/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:52:20 by abin-saa          #+#    #+#             */
/*   Updated: 2022/05/19 11:38:17 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*ds;
	char	*sr;

	ds = (char *)dst;
	sr = (char *)src;
	if (sr == ds)
		return (dst);
	if (sr < ds)
	{
		while (len--)
		{
			*(ds + len) = *(sr + len);
		}
		return (dst);
	}
	else
	{
		while (len--)
		{
		*ds++ = *sr++;
		}
	}
	return (dst);
}

// int main()
// {
//     char s[] = "mansdf";
//     char d[] = "cer";

//     printf("n: %s",ft_memmove(d, s,4));
// }
