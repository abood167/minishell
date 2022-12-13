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
	int	i;
	int	wordcount;
	int quote;

	i = 0;
	quote = 0;
	wordcount = 0;
	while (str[i] != '\0')
	{
		if (!quote && (str[i] == '\"' || str[i] == '\'')) {
			if (i && str[i - 1] != c)
				wordcount--;
			quote = str[i];
		}
		else if (quote && quote == str[i]) {
			quote = 0;
			wordcount++;
		}
		else if (!quote && i == 0 && c != str[i])
			wordcount++;
		else if (!quote && c != str[i] && c == str[i - 1])
			wordcount++;
		i++;
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
		if (src[i] == '\'' || src[i] == '\"') {
			if (quote == 0) {
				quote = src[i++];
				continue;
			}
			else if (quote == src[i]) {
				quote = 0;
				i++;
				continue;
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

char	*ft_substrquote(char const *s, unsigned int start, size_t len, int quote)
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
		if (quote > 0){
			while (a[i] != quote)
				i++;
			return(&a[i]);
		}
		else if (quote < 0) {
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

static char	**ft_splitquote2(char **split, char const *s, char c, int *word)
{
	char	*str;
	int quote;

	str = (char *)s;
	while (str && *str != '\0')
	{
		quote = 0;
		while ((*str == c) && *str != '\0')
			str++;
		if (*str  == '\'' || *str  == '\"') {
			quote = *str;
			str++;
		}
		if (ft_strchr(str, c))
		{
			split[(*word)++] = ft_substrquote(str, 0, (size_t)(ft_strchrquote(str, c, quote) - str), quote);
			quote *= -1;
			for (int i = 0; i < *word ; i++)
				// ft_printf("test %d: %s\n", *word, split[i]);
				if (!split[*word - 1])
				{
				// ft_printf("reach 1\n");
					// ft_freearray((void **)split);
					return (NULL);
				}
			str = ft_strchrquote(str, c, quote);
		}
		else if (*str != '\0')
		{
			split[(*word)++] = ft_substrquote(str, 0, ft_strlen(str), quote);
			break ;
		}
	}
	// for (int i = 0; split[i]; i++)
	// 	ft_printf("end: %s\n", split[i]);
	return (split);
}

char	**ft_splitquote(char const *s)
{
	char	**split;
	int		word;

	if (!s)
		return (NULL);
	split = (char **)malloc(sizeof(char *) * (wordcount(s, ' ') + 1));
	if (!split)
		return (NULL);
	word = 0;
	if (!ft_splitquote2(split, s, ' ', &word))
		return (NULL);
	split[word] = 0;
	return (split);
}

// int main () {
// 	//
// 	// char *str = "asd asdasd \"asdasd asdas\"";
// 	// char *str = "asda asd \"asdasdasd       asd\"";
// 	// char *str = "asuadsjkdas \"Asdasd\" asdasd asd ss\"asdasd asdasd asdasd\"ss"; //need to fix
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