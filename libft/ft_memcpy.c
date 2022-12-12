/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:23:28 by abin-saa          #+#    #+#             */
/*   Updated: 2022/06/02 14:17:36 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void	*dst, const void	*src, size_t n)
{
	char	*dst_bytes;
	char	*src_bytes;
	size_t	i;

	i = 0;
	dst_bytes = (char *)dst;
	src_bytes = (char *)src;
	if (dst == src)
		return (dst);
	while (i < n)
	{
		dst_bytes[i] = src_bytes[i];
		i++;
	}
	return (dst);
}

// 	int main() 
// {
//     char m[4] = "sde";
//     char n[4];
//     ft_memcpy(n, m, 4);
//     printf("n: %s\n", n);

// }