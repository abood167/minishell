/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 05:40:01 by sbokhari          #+#    #+#             */
/*   Updated: 2023/01/10 12:51:13 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*strip_copy(char *str, int len, int brace)
{
	char	*strip;
	char	*word;
	int		i;
	int		j;
	int		quote;

	init_zero(&i, &j, &quote, NULL);
	strip = (char *)malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		if (!in_quote(str[j], &quote) && !in_brace(&brace, str[j])
			&& (str[j] == '<' || str[j] == '>'))
		{
			j += 1 + (str[j + 1] == '<' || str[j + 1] == '>');
			word = get_next_word(str, &j, ' ');
			free(word);
			continue ;
		}
		strip[i++] = str[j++];
	}
	free(str);
	strip[i] = '\0';
	return (strip);
}

static int	syntax_check(char *line, char *word, int i, int ignoreS)
{
	if (!word || (line[i - 1] != '\'' && line[i - 1] != '\"' && (word[0] == '&'
				|| word[0] == '|' || (!ignoreS && word[0] == '*')
				|| word[0] == '<'
				|| word[0] == '>' || word[0] == '(' || word[0] == ')')))
	{
		free(word);
		syntax_error(word);
		return (1);
	}
	return (0);
}

int	strip_redirect3(char *line, t_mini *m, int test, int *i)
{
	char	*word;

	if (ft_strncmp(&line[*i], "<<", 2) == 0)
	{
		(*i) += 2;
		word = get_next_word(line, i, ' ');
		if (syntax_check(line, word, *i, 1))
			return (alt_free(line, 0) || ((*i) = 0));
		if (!test)
			str_doc(m);
		return (alt_free(word, 1));
	}
	else if (ft_strncmp(&line[*i], "<", 1) == 0)
	{
		(*i)++;
		word = get_next_word(line, i, ' ');
		if (syntax_check(line, word, *i, 0))
			return (alt_free(line, 0) || ((*i) = 0));
		if (!test && !alt_open(&m->in, word, O_RDONLY, 0))
			return (alt_free(line, 0) || ((*i) = 0));
		return (alt_free(word, 1));
	}
	return (-1);
}

int	strip_redirect2(char *line, t_mini *m, int test, int *i)
{
	char	*word;

	if (ft_strncmp(&line[*i], ">>", 2) == 0)
	{
		(*i) += 2;
		word = get_next_word(line, i, ' ');
		if (syntax_check(line, word, *i, 0))
			return (alt_free(line, 0) || ((*i) = 0));
		if (!test && !alt_open(&m->out[1], word, O_CREAT | O_WRONLY | O_APPEND,
				1))
			return (alt_free(line, 0) || ((*i) = 0));
		return (alt_free(word, 1));
	}
	else if (ft_strncmp(&line[*i], ">", 1) == 0)
	{
		(*i)++;
		word = get_next_word(line, i, ' ');
		if (syntax_check(line, word, *i, 0))
			return (alt_free(line, 0) || ((*i) = 0));
		if (!test && !alt_open(&m->out[1], word, O_CREAT | O_WRONLY | O_TRUNC,
				1))
			return (alt_free(line, 0) || ((*i) = 0));
		return (alt_free(word, 1));
	}
	return (-1);
}

char	*strip_redirect(char *line, t_mini *m, int test, int brace)
{
	int	len;

	init_zero(&len, &m->quote, &m->i, NULL);
	while (line[m->i])
	{
		if (in_quote(line[m->i], &m->quote) || in_brace(&brace, line[m->i]))
		{
			m->i++;
			len++;
			continue ;
		}
		else if (strip_redirect2(line, m, test, &m->i) >= 0
			|| strip_redirect3(line, m, test, &m->i) >= 0)
		{
			if (m->i == 0)
				return (NULL);
		}
		else
		{
			m->i++;
			len++;
		}
	}
	return (strip_copy(line, len, brace));
}
