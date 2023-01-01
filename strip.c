#include "minishell.h"

static char	*strip_copy(char *str, int len)
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
			if (ft_strncmp(&str[j], ">>", 2) == 0 || ft_strncmp(&str[j], "<<",
					2) == 0)
			{
				j += 2;
				word = get_next_word(str, &j, ' ');
				free(word);
				continue ;
			}
			else if (ft_strncmp(&str[j], ">", 1) == 0 || ft_strncmp(&str[j], "<",
						1) == 0)
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

char	*strip_redirect(char *line, t_mini *m, int test)
{
	int len;
	int quote;
	char *word;

	len = 0;
	quote = 0;
	int i = 0;
	while (line[i])
	{
		if (in_quote(line[i], &quote))
			(void)NULL;
		else if (ft_strncmp(&line[i], ">>", 2) == 0)
		{
			i += 2;
			word = get_next_word(line, &i, ' '); 
			if (!word || (word && (word[0] == '&' || word[0] == '|' || word[0] == '*' || word[0] == '<' || word[0] == '>')))
			{
				syntax_error(word);
				return (NULL);
			}
			if (!test && !alt_open(&m->out[1], word, O_CREAT | O_WRONLY | O_APPEND, 1))
				return (NULL);
			free(word);
		}
		else if (ft_strncmp(&line[i], ">", 1) == 0)
		{
			i++;
			word = get_next_word(line, &i, ' ');
			if (!word || (word && (word[0] == '&' || word[0] == '|' || word[0] == '*' || word[0] == '<' || word[0] == '>')))
			{
				syntax_error(word);
				return (NULL);
			}
			if (!test && !alt_open(&m->out[1], word, O_CREAT | O_WRONLY | O_TRUNC, 1))
				return (NULL);
			free(word);
		}
		else if (ft_strncmp(&line[i], "<<", 2) == 0)
		{
			i += 2;
			word = get_next_word(line, &i, ' ');
			if (!word || (word && (word[0] == '&' || word[0] == '|' || word[0] == '<' || word[0] == '>')))
			{
				syntax_error(word);
				return (NULL);
			}
			if(!test) 
				str_doc(m); //handle error
			free(word);
		}
		else if (ft_strncmp(&line[i], "<", 1) == 0)
		{
			i++;
			word = get_next_word(line, &i, ' ');
			if (!word || (word && (word[0] == '&' || word[0] == '|' || word[0] == '*' || word[0] == '<' || word[0] == '>')))
			{
				syntax_error(word);
				return (NULL);
			}
			if (!test && !alt_open(&m->in, word, O_RDONLY, 0))
				return (NULL);
			free(word);
		}
		i++;
		len++;
	}
	return (strip_copy(line, len));
}
