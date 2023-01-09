/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_qoute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:01:49 by abin-saa          #+#    #+#             */
/*   Updated: 2023/01/06 05:40:09 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**get_next_word2(const char *str, int *pos, char c, int count[])
{
	int		quote;
	char	**words;

	words = (char **)malloc(sizeof(char *) * (count[0] + 1));
	init_zero(&count[0], (int *)(intptr_t)((*pos = count[1]) && 0), &quote,
			NULL);
	while (str[*pos] && str[*pos] != c && str[*pos] != ')')
	{
		count[1] = *pos;
		if (in_quote(str[*pos], &quote) == 2)
		{
			count[1] = ++(*pos);
			while (in_quote(str[*pos], &quote) != 1)
				(*pos)++;
			words[count[0]++] = ft_substr(str, count[1], (*pos)++ - count[1]);
			continue ;
		}
		while (str[*pos] && str[*pos] != c && str[*pos] != ')'
			&& !in_quote(str[*pos], &quote))
			(*pos)++;
		words[count[0]++] = ft_substr(str, count[1], *pos - count[1]);
		quote = 0;
	}
	words[count[0]] = NULL;
	return (words);
}

char	*get_next_word(const char *str, int *pos, char c)
{
	int		quote;
	int		count[2];
	char	**words;

	init_zero(&quote, &count[0], NULL, NULL);
	while (str[*pos] && str[*pos] == c)
		(*pos)++;
	if (!str[*pos])
		return (NULL);
	count[1] = *pos;
	while (str[*pos] && ((str[*pos] != c && str[*pos] != ')') || quote))
	{
		if (in_quote(str[*pos], &quote) == 2 || *pos - count[1] == 0)
			count[0]++;
		else if (!quote && *pos - count[1] && in_quote(str[*pos - 1], &quote))
			init_zero(&quote, (int *)(intptr_t)(count[0]++ && 0), NULL, NULL);
		(*pos)++;
	}
	if (quote)
		return (NULL);
	words = get_next_word2(str, pos, c, count);
	return (arrtostr(words, 1));
}

int	in_quote(char c, int *quote)
{
	if (c == '\'' || c == '\"')
	{
		if (c == *quote)
		{
			*quote = 0;
			return (1);
		}
		else if (!*quote)
		{
			*quote = c;
			return (2);
		}
	}
	else if (*quote)
		return (3);
	return (0);
}

char	**ft_splitquote(char *s, char c)
{
	char	**split;
	int		word;
	int		i;

	word = 0;
	i = 0;
	if (!s)
		return (NULL);
	split = (char **)malloc(sizeof(char *) * (wordcount(s, c) + 1));
	if (!split)
		return (NULL);
	while (1)
	{
		split[word] = get_next_word(s, &i, c);
		if (!split[word])
			break ;
		word++;
	}
	return (split);
}
