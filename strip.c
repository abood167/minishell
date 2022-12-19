#include "minishell.h"

char	*strip_copy(char *str, int len)
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

char	*strip_redirect(char *line, t_pipex *pipex, int test)
{
	int len;
	int quote;
	char *word;

	len = 0;
	quote = 0;
	for (int i = 0; line[i]; i++)
	{
		if (in_quote(line[i], &quote))
		{
			len++;
			continue ;
		}
		if (ft_strncmp(&line[i], ">>", 2) == 0)
		{
			i += 2;
			word = get_next_word(line, &i, ' '); //handle special character
			if (!word || (word && (word[0] == '&' || word[0] == '|' || word[0] == '*')))
			{
				syntax_error(word);
				return (NULL);
			}
			// Handle closing if out is not -1
			if(!test) {
				pipex->out[1] = open(word, O_CREAT | O_WRONLY | O_APPEND, 0644);
				if (pipex->out[1] < 0)
				{
					ft_putstr_fd("minishell: ", 2);
					perror(word);
					free(word);
					return (NULL);
				}
			}
			free(word);
		}
		else if (ft_strncmp(&line[i], ">", 1) == 0)
		{
			i++;
			word = get_next_word(line, &i, ' ');
			if (!word || (word && (word[0] == '&' || word[0] == '|' || word[0] == '*')))
			{
				syntax_error(word);
				return (NULL);
			}
			// Handle closing if out is not -1
			if(!test) {
				pipex->out[1] = open(word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
				if (pipex->out[1] < 0)
				{
					ft_putstr_fd("minishell: ", 2);
					perror(word);
					free(word);
					return (NULL);
				}
			}
			free(word);
		}
		else if (ft_strncmp(&line[i], "<<", 2) == 0)
		{
			i += 2;
			word = get_next_word(line, &i, ' ');
			if (!word || (word && (word[0] == '&' || word[0] == '|')))
			{
				syntax_error(word);
				return (NULL);
			}

			// Handle closing if in/out is not -1
			if(!test) 
				here_doc(pipex, word); //handle error
			free(word);
			if(pipex->status != 0)
				return NULL;
		}
		else if (ft_strncmp(&line[i], "<", 1) == 0)
		{
			i++;
			word = get_next_word(line, &i, ' ');
			if (!word || (word && (word[0] == '&' || word[0] == '|' || word[0] == '*')))
			{
				syntax_error(word);
				return (NULL);
			}
			// Handle closing if in is not -1
			if(!test) {
				pipex->in = open(word, O_RDONLY);
				if (pipex->in < 0)
				{
					ft_putstr_fd("minishell: ", 2);
					perror(word);
					free(word);
					return (NULL);
				}
			}
			free(word);
		}
		len++;
	}
	return (strip_copy(line, len));
}