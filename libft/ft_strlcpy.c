/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:28:51 by abin-saa          #+#    #+#             */
/*   Updated: 2022/05/18 18:12:20 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	ss;

	i = 0;
	ss = ft_strlen(src);
	if (dstsize == 0)
		return (ss);
	if (ft_strlen(src) == 0)
	{
		dst[0] = '\0';
		return (ft_strlen(src));
	}
	while (i < (dstsize - 1) && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ss);
}

// int main()
// {
//     char d[] = {"reeem"};
//     char s[] = {""};
// 	char src[] = "coucou";
// 	char dest[10]; memset(dest, 'A', 10);
// 	ft_strlcpy(dest, src, 0);
// 	ft_strlcpy(dest, src, 1);
// 	size_t i = ft_strlcpy(dest, src, 2);
// 	if (i == strlen(src))
// 		printf("hi0\n");
// 	if ( dest[0] == 'c')
// 		printf("hi1\n");
// 	if (dest[1] == 0)
// 		printf("hi2\n");
// 	if (dest[2] == 'A')
// 		printf("hi3\n");
// 	// if (!strcmp(src, dest))
// 	// 	printf("hi4\n");
// 	// if ()
//     // printf("d: %zu \n",ft_strlcpy(d,s,3));
// 	// printf("%s\n",d);
// 	// int x;
// 	// x = strlcpy(d,s,3);
// 	// printf("Right answer %s\n",s);
//     // return (0);
// }