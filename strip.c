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

static char	*strip_copy(char *str, int len, int brace)
{
	char	*strip;
	char	*word;
	int		i;
	int		j;
	int		quote;

	i = 0;
	j = 0;
	quote = 0;
	strip = (char *)malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		if (!in_quote(str[j], &quote))
		{
			if (brace && str[j] == '(')
			{
				brace++;
			}
			else if (brace && str[j] == ')')
			{
				brace--;
			}
			else if (brace > 1)
				(void)NULL;
			else if (ft_strncmp(&str[j], ">>", 2) == 0 || ft_strncmp(&str[j],
						"<<", 2) == 0)
			{
				j += 2;
				word = get_next_word(str, &j, ' ');
				free(word);
				continue ;
			}
			else if (ft_strncmp(&str[j], ">", 1) == 0 || ft_strncmp(&str[j],
						"<", 1) == 0)
			{
				j += 1;
				word = get_next_word(str, &j, ' ');
				free(word);
				continue ;
			}
		}
		strip[i] = str[j];
		i++;
		j++;
	}
	free(str);
	strip[i] = '\0';
	return (strip);
}

char	*strip_redirect(char *line, t_mini *m, int test, int brace)
{
	int		len;
	int		quote;
	char	*word;
	int		i;

	len = 0;
	quote = 0;
	i = 0;
	while (line[i])
	{
		if (in_quote(line[i], &quote))
		{
			i++;
			len++;
		}
		else if (brace && line[i] == '(')
		{
			i++;
			len++;
			brace++;
		}
		else if (brace && line[i] == ')')
		{
			i++;
			len++;
			brace--;
		}
		else if (brace > 1)
		{
			i++;
			len++;
		}
		else if (ft_strncmp(&line[i], ">>", 2) == 0)
		{
			i += 2;
			word = get_next_word(line, &i, ' ');
			if (!word || (line[i - 1] != '\'' && line[i - 1] != '\"'
					&& (word[0] == '&' || word[0] == '|' || word[0] == '*'
					|| word[0] == '<' || word[0] == '>' || word[0] == '('
					|| word[0] == ')')))
			{
				syntax_error(word);
				return ((void*)(intptr_t)alt_free(line, 0));
			}
			if (!test && !alt_open(&m->out[1], word,
					O_CREAT | O_WRONLY | O_APPEND, 1))
				return ((void*)(intptr_t)alt_free(line, 0));
			free(word);
		}
		else if (ft_strncmp(&line[i], ">", 1) == 0)
		{
			i++;
			word = get_next_word(line, &i, ' ');
			if (!word || (line[i - 1] != '\'' && line[i - 1] != '\"'
					&& (word[0] == '&' || word[0] == '|' || word[0] == '*'
					|| word[0] == '<' || word[0] == '>' || word[0] == '('
					|| word[0] == ')')))
			{
				syntax_error(word);
				return ((void*)(intptr_t)alt_free(line, 0));
			}
			if (!test && !alt_open(&m->out[1], word,
					O_CREAT | O_WRONLY | O_TRUNC, 1))
				return ((void*)(intptr_t)alt_free(line, 0));
			free(word);
		}
		else if (ft_strncmp(&line[i], "<<", 2) == 0)
		{
			i += 2;
			word = get_next_word(line, &i, ' ');
			if (!word || (line[i - 1] != '\'' && line[i - 1] != '\"'
					&& (word[0] == '&' || word[0] == '|' || word[0] == '<'
					|| word[0] == '>' || word[0] == '(' || word[0] == ')')))
			{
				syntax_error(word);
				return ((void*)(intptr_t)alt_free(line, 0));
			}
			if (!test)
				str_doc(m); //handle error
			free(word);
		}
		else if (ft_strncmp(&line[i], "<", 1) == 0)
		{
			i++;
			word = get_next_word(line, &i, ' ');
			if (!word || (line[i - 1] != '\'' && line[i - 1] != '\"'
					&& (word[0] == '&' || word[0] == '|' || word[0] == '*'
					|| word[0] == '<' || word[0] == '>' || word[0] == '('
					|| word[0] == ')')))
			{
				syntax_error(word);
				return ((void*)(intptr_t)alt_free(line, 0));
			}
			if (!test && !alt_open(&m->in, word, O_RDONLY, 0))
				return ((void*)(intptr_t)alt_free(line, 0));
			free(word);
		}
		else
		{
			i++;
			len++;
		}
	}
	return (strip_copy(line, len, brace));
}
