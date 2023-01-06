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

char	*get_next_word(const char *str, int *pos, char c)
{
	int		quote;
	int		start;
	int		count;
	char	**words;
	char	*line;

	quote = 0;
	count = 0;
	while (str[*pos] && str[*pos] == c)
		(*pos)++;
	if (!str[*pos])
		return (NULL);
	start = *pos;
	while (str[*pos] && ((str[*pos] != c && str[*pos] != ')') || quote))
	{
		if (in_quote(str[*pos], &quote) == 2)
			count++;
		else if (*pos - start == 0)
			count++;
		else if (!quote && *pos - start && in_quote(str[*pos - 1], &quote))
		{
			quote = 0;
			count++;
		}
		(*pos)++;
	}
	if (quote)
		return (NULL); //Quotes did not close
	words = (char **)malloc(sizeof(char *) * (count + 1));
	*pos = start;
	count = 0;
	while (str[*pos] && str[*pos] != c && str[*pos] != ')')
	{
		start = *pos;
		if (in_quote(str[*pos], &quote) == 2)
		{
			start = ++(*pos);
			while (in_quote(str[*pos], &quote) != 1)
				(*pos)++;
			words[count++] = ft_substr(str, start, *pos - start);
			(*pos)++;
		}
		else
		{
			while (str[*pos] && str[*pos] != c && str[*pos] != ')'
				&& !in_quote(str[*pos], &quote))
				(*pos)++;
			words[count++] = ft_substr(str, start, *pos - start);
			if (quote)
				quote = 0;
		}
	}
	words[count] = NULL;
	line = arrtostr(words);
	ft_freearray((void **)words);
	return (line);
}

int	in_quote(char c, int *quote)
{
	if (c == '\'' || c == '\"')
	{
		if (c == *quote)
		{
			*quote = 0;
			return (1); //close
		}
		else if (!*quote)
		{
			*quote = c;
			return (2); //open
		}
	}
	else if (*quote)
		return (3); //ingore quote
	return (0);     //not in quote
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
		//maybe check if word count matches, if not free then return null
	}
	return (split);
}
