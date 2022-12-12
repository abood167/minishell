/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 17:48:28 by abin-saa          #+#    #+#             */
/*   Updated: 2022/06/02 16:17:43 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*abood;

	if ((size != 0 && count > SIZE_MAX / size))
		return (NULL);
	abood = malloc ((count * size));
	if (!abood)
		return (NULL);
	ft_bzero (abood, (count * size));
	return (abood);
}
