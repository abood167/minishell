/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:34:11 by abin-saa          #+#    #+#             */
/*   Updated: 2022/05/18 17:24:37 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if ((char)c == s[i])
		{
			return ((char *)&s[i]);
		}
		i--;
	}
	return (0);
}

// int main ()
// {
// 	char s[] = "hi my frinde";
// 	char i = 'i';
// 	printf("%s", ft_strrchr(s,i));
// }
