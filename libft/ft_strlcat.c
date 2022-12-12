/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 09:31:28 by abin-saa          #+#    #+#             */
/*   Updated: 2022/05/23 11:06:47 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	x;
	size_t	y;

	i = 0;
	x = ft_strlen(src);
	y = ft_strlen(dst);
	if (y > dstsize)
		y = dstsize;
	if (dstsize > 0 && y < dstsize - 1)
	{
		while (y + i < (dstsize - 1) && (src[i] != '\0'))
		{
			dst[y + i] = src[i];
			i++;
		}
		dst[y + i] = '\0';
	}
	return (y + x);
}

/*int main()
{
    char s[] = "as";
    char d[]  = "dddd";

    printf("d: %zu\n", ft_strlcat(d,s, 5));

}
*/
