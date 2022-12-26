/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbokhari <sbokhari@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 21:45:39 by sbokhari          #+#    #+#             */
/*   Updated: 2022/07/17 16:05:58 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;

	if (size && nmemb > SIZE_MAX / size)
		return (NULL);
	mem = malloc(nmemb * size);
	if (mem != NULL)
		ft_memset(mem, 0, nmemb * size);
	return (mem);
}

void	ft_freearray(void **arr)
{
	size_t	i;

	i = 0;
	if(arr) {
		while (arr[i])
			free(arr[i++]);
		free(arr);
	}
}

int	ft_2dlen(void **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
