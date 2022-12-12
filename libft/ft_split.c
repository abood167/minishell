/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:33:50 by abin-saa          #+#    #+#             */
/*   Updated: 2022/12/12 11:52:34 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_undoalloc(char *s, int i)
{
	while (i >= 0)
	{
		free(&s[i]);
		i--;
	}
	free (s);
}

static	int	ft_worddet(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && (s[i] != c))
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static	char	*ft_cpystr(char const *s, char c)
{
	size_t	i;
	char	*str;

	i = 0;
	while (s[i] && s[i] != c)
	{
		i++;
	}
	str = (char *)ft_calloc((i + 1), sizeof(char));
	if (!str)
		return (0);
	ft_memcpy(str, s, i);
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		count;
	char	**split;

	if (!s)
		return (0);
	count = ft_worddet(s, c);
	split = (((char **) malloc (sizeof(char *) * (count + 1))));
	if (!split)
		return (0);
	i = 0;
	while (i < count)
	{
		while (*s == c)
			s++;
		split[i] = ft_cpystr(s, c);
		if (!split[i])
			ft_undoalloc(*split, i);
		s += ft_strlen(split[i]);
		i++;
	}
	split[i] = 0;
	return (split);
}

// int main()
// {
// 	int i = 0;
// 	char a[] = "   My  Name  Is abood 19.3 years ";
// 	char	**split = ft_split(a, ' ');
// 	while (split[i])
// 	{
// 		printf("%s \n", split[i]);
// 		i++;
// 	}
// }
