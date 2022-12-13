/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_handler2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbokhari <sbokhari@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:06:05 by sbokhari          #+#    #+#             */
/*   Updated: 2022/07/17 16:06:24 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_contains(char const *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	char	*a;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	a = (char *)s;
	while (a[i])
	{
		if (a[i] == (char)c)
			return (&a[i]);
		i++;
	}
	if (a[i] == (char)c)
		return (&a[i]);
	return (NULL);
}

char	*ft_strrchr(const char *s, int c)
{
	char	*a;
	int		i;

	i = ft_strlen(s);
	a = (char *)s;
	while (i)
	{
		if (a[i] == (char)c)
			return (&a[i]);
		i--;
	}
	if (a[i] == (char)c)
		return (&a[i]);
	return (NULL);
}

char	*ft_strstr(const char *str, const char *to_find)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (to_find[i] == '\0')
		return ((char *)str);
	while (str[i] != '\0')
	{
		j = 0;
		if (str[i] == to_find[j])
		{
			while (str[i + j] == to_find[j])
			{
				if (to_find[j + 1] == '\0')
					return ((char *)&str[i]);
				j++;
			}
		}
		i++;
	}
	return (0);
}

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (to_find[i] == '\0')
		return ((char *)str);
	while (str[i] != '\0' && i < len)
	{
		j = 0;
		if (str[i] == to_find[j])
		{
			while (str[i + j] == to_find[j] && i + j < len)
			{
				if (to_find[j + 1] == '\0')
					return ((char *)&str[i]);
				j++;
			}
		}
		i++;
	}
	return (0);
}
