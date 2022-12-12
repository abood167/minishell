/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:05:52 by abin-saa          #+#    #+#             */
/*   Updated: 2022/06/02 16:01:21 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}

/*int main()
{

    char bytes[5] = {1, 'j', 3,4,'x'};
    ft_bzero(bytes, 5);
    int i = 0;
    while (i < 5)
    {
        printf("%d, ", bytes[i]);
        i++;

    }
    return (0);
}
*/
