/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_qoute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:01:49 by abin-saa          #+#    #+#             */
/*   Updated: 2022/12/12 12:03:07 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minshell.h"

static int	wordcount(char const *str, char c)
{
	int		wordcount;
	char	*word;
	int		i;

	wordcount = 0;
	i = 0;
	while (1)
	{
		word = get_next_word(str, &i, c);
		if (!word)
			break ;
		free(word);
		wordcount++;
	}
	return (wordcount);
}

size_t	ft_strlcpyquote(char *dst, const char *src, size_t dstsize, int quote)
{
	size_t	i;
	size_t	j;

	if (!dstsize)
		return (ft_strlen(src));
	i = 0;
	j = 0;
	while (src[i] != '\0' && i < dstsize - 1)
	{
		if (src[i] == '\'' || src[i] == '\"')
		{
			if (quote == 0)
			{
				quote = src[i++];
				continue ;
			}
			else if (quote == src[i])
			{
				quote = 0;
				i++;
				continue ;
			}
		}
		dst[j] = src[i];
		i++;
		j++;
	}
	if (dstsize > 0)
		dst[j] = '\0';
	return (ft_strlen(src));
}

char	*ft_substrquote(char const *s, unsigned int start, size_t len,
		int quote)
{
	char	*substr;
	size_t	i;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
		i = 0;
	else
	{
		i = ft_strlen(&s[start]);
		if (i > len)
			i = len;
	}
	substr = (char *)malloc(sizeof(char) * i + 1);
	if (!substr)
		return (NULL);
	ft_strlcpyquote(substr, &s[start], i + 1, quote);
	return (substr);
}

char	*ft_strchrquote(const char *s, int c, int quote)
{
	char	*a;
	int		i;

	i = 0;
	a = (char *)s;
	while (a[i])
	{
		if (quote > 0)
		{
			while (a[i] != quote)
				i++;
			return (&a[i]);
		}
		else if (quote < 0)
		{
			while (a[i] != -quote)
				i++;
			quote = 0;
		}
		if (a[i] == (char)c)
			return (&a[i]);
		i++;
	}
	if (a[i] == (char)c)
		return (&a[i]);
	return (NULL);
}

static char	**ft_splitquote2(char **split, char const *s, char c)
{
	int	word;
	int	i;

	word = 0;
	i = 0;
	while (1)
	{
		split[word] = get_next_word(s, &i, c);
		if (!split[word])
			break ;
		word++;
	}
	return (split);
}

char	**ft_splitquote(char *s, char c)
{
	char	**split;

	if (!s)
		return (NULL);
	split = (char **)malloc(sizeof(char *) * (wordcount(s, c) + 1));
	if (!split)
		return (NULL);
	if (!ft_splitquote2(split, s, c))
		return (NULL);
	return (split);
}

// int main () {
// 	//
// 	// char *str = "asd asdasd \"asdasd asdas\"";
// 	// char *str = "asda asd \"asdasdasd       asd\"";
// 	// char *str = "asuadsjkdas \"Asdasd\" asdasd asd ss\"asdasd asdasd asdasd\"ss";
		//need to fix
// 	char *str = " asd asd \"asdasd  asd\"\n";
// 	// char *str = get_next_line(0);
// 	ft_printf("str: %s\n", str);
// 	ft_printf("WC: %d\n", wordcount(str, ' '));
// 	char **split = ft_splitquote(str, ' ');
// 	int i;
// 	for (i = 0; split[i]; i++);
// 	ft_printf("ARR: %d\n", i);

// 	for (i = 0; split[i]; i++)
// 		ft_printf("%s\n", split[i]);
// }