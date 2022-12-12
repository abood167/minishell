/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:23:19 by abin-saa          #+#    #+#             */
/*   Updated: 2022/05/17 11:51:40 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i ;
	char	*bytes;

	bytes = b ;
	i = 0;
	while (i < len)
	{
	bytes [i] = c;
	i++;
	}
	return (b);
}

/*int main ( int argc, char *argv[])
  {
    char arr1[] = { 3, 4};
    char arr2[] = { 1, 2} ;
    ft_memset(arr1, 1, 2 * sizeof(char));
    printf("%d %d\n", arr1[0], arr1[1]);
    return (0);
  }*/
