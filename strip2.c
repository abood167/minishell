#include "minishell.h"

void	strip_heredoc(char *line, t_mini *m)
{
	int len;
	int quote;
	char *word;

	len = 0;
	quote = 0;
	m->status = 0;
	for (int i = 0; line[i]; i++)
	{
		if (in_quote(line[i], &quote))
		{
			len++;
			continue ;
		}
		if (ft_strncmp(&line[i], "<<", 2) == 0)
		{
			i += 2;
			word = get_next_word(line, &i, ' ');
			// Handle closing if in/out is not -1
			here_doc(m, word); //handle error
			free(word);
		}
		len++;
	}
}

void	heredoc_count(char *line, int *cnt)
{
	int len;
	int quote;

	quote = 0;
	for (int i = 0; line[i]; i++)
	{
		if (in_quote(line[i], &quote))
		{
			len++;
			continue ;
		}
		if (ft_strncmp(&line[i], "<<", 2) == 0)
		{
			i += 2;
			(*cnt)++;
		}
	}
}

void	str_doc(t_mini *m)
{
	int		old_out;

	old_out = m->out[1];
	if (pipe(m->out) == -1)
		error_exit("Pipe: ");
	ft_putstr_fd(ft_lstindex(m->doc_str, m->here_doc++)->content, m->out[1]);
	write(m->out[1], "\0", 1);
	if (m->in != 0)
		close(m->in);
	close(m->out[1]);
	m->out[1] = old_out;
	m->in = m->out[0];
}
