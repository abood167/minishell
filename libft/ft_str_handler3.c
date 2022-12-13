/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_handler3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbokhari <sbokhari@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:06:19 by sbokhari          #+#    #+#             */
/*   Updated: 2022/07/17 16:06:24 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static int	wordcount(char const *str, char c)
{
	int	i;
	int	wordcount;

	i = 0;
	wordcount = 0;
	while (str[i] != '\0')
	{
		if (i == 0 && c != str[i])
			wordcount++;
		else if (c != str[i] && c == str[i - 1])
			wordcount++;
		i++;
	}
	return (wordcount);
}

static char	**ft_split2(char **split, char const *s, char c, int *word)
{
	char	*str;

	str = (char *)s;
	while (*str != '\0')
	{
		while (*str == c && *str != '\0')
			str++;
		if (ft_strchr(str, c))
		{
			split[(*word)++] = ft_substr(str, 0, (size_t)(ft_strchr(str, c)
						- str));
			if (!split[*word - 1])
			{
				ft_freearray((void **)split);
				return (NULL);
			}
			str = ft_strchr(str, c);
		}
		else if (*str != '\0')
		{
			split[(*word)++] = ft_strdup(str);
			break ;
		}
	}
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		word;

	if (!s)
		return (NULL);
	split = (char **)malloc(sizeof(char *) * (wordcount(s, c) + 1));
	if (!split)
		return (NULL);
	word = 0;
	if (!ft_split2(split, s, c, &word))
		return (NULL);
	split[word] = 0;
	return (split);
}
