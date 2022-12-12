/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 17:34:25 by abin-saa          #+#    #+#             */
/*   Updated: 2022/05/18 15:28:13 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*mm;
	unsigned char	*nn;

	mm = (unsigned char *)s1;
	nn = (unsigned char *)s2;
	i = 0;
	if (n == '\0')
		return (0);
	while (i < n)
	{
		if (mm[i] == nn[i] && mm[i] != '\0' && nn[i] != '\0')
			i++;
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}

// int main()
// {
//     char s1[] = "abc";
//    char s2[] = "ab";
//    printf("%d", ft_strncmp(s1,s2,3));
// }