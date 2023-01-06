/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbokhari <sbokhari@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 05:40:01 by sbokhari          #+#    #+#             */
/*   Updated: 2023/01/06 05:41:23 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_brace(int *brace, char c)
{
	if (*brace && c == '(')
	{
		(*brace)++;
		return 1;
	}
	else if (*brace && c == ')')
	{
		(*brace)--;
		return (1);
	}
	else if (*brace > 1)
		return (1);
	return (0);
}

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
		if (!in_quote(str[j], &quote) && in_brace(&brace, str[j])
			&& (str[j] == '<' || str[j] == '>'))
		{
			j = 1 + (str[j + 1] == '<' || str[j + 1] == '>');
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

static int syntax_check(char *line, char *word, int i, int ignoreS) {
	
	if (!word || (line[i - 1] != '\'' && line[i - 1] != '\"'
			&& (word[0] == '&' || word[0] == '|' || (!ignoreS && word[0] == '*')
			|| word[0] == '<' || word[0] == '>' || word[0] == '('
			|| word[0] == ')')))
	{
		free(word);
		syntax_error(word);
		return 1;
	}
	return 0;
}

char	*strip_redirect(char *line, t_mini *m, int test, int brace)
{
	int		len;
	int		quote;
	char	*word;
	int		i;

	word = init_zero(&len, &quote, &i, NULL);
	while (line[i])
	{
		if (in_quote(line[i], &quote) || in_brace(&brace, line[i]))
		{
			i++;
			len++;
		}
		else if (ft_strncmp(&line[i], ">>", 2) == 0)
		{
			i += 2;
			word = get_next_word(line, &i, ' ');
			if(syntax_check(line, word, i, 0))
				return ((void *)(intptr_t)alt_free(line, 0));
			if (!test && !alt_open(&m->out[1], word,
					O_CREAT | O_WRONLY | O_APPEND, 1))
				return ((void *)(intptr_t)((alt_free(line, 0)) || alt_free(word, 0)));
		}
		else if (ft_strncmp(&line[i], ">", 1) == 0)
		{
			i++;
			word = get_next_word(line, &i, ' ');
			if(syntax_check(line, word, i, 0))
				return ((void *)(intptr_t)alt_free(line, 0));
			if (!test && !alt_open(&m->out[1], word,
					O_CREAT | O_WRONLY | O_TRUNC, 1))
				return ((void *)(intptr_t)((alt_free(line, 0)) || alt_free(word, 0)));
		}
		else if (ft_strncmp(&line[i], "<<", 2) == 0)
		{
			i += 2;
			word = get_next_word(line, &i, ' ');
			if(syntax_check(line, word, i, 1))
				return ((void *)(intptr_t)alt_free(line, 0));
			if (!test)
				str_doc(m);
		}
		else if (ft_strncmp(&line[i], "<", 1) == 0)
		{
			i++;
			word = get_next_word(line, &i, ' ');
			if(syntax_check(line, word, i, 0))
				return ((void *)(intptr_t)alt_free(line, 0));
			if (!test && !alt_open(&m->in, word, O_RDONLY, 0))
				return ((void *)(intptr_t)((alt_free(line, 0)) || alt_free(word, 0)));
		}
		else
		{
			i++;
			len++;
		}
		word = (void *)(intptr_t)alt_free(word, 0);
	}
	return (strip_copy(line, len, brace));
}
