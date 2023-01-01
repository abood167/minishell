#include "minishell.h"

int	strip_heredoc(char *line, t_mini *m)
{
	int len;
	int quote;
	char *word;
	int  bak;

	len = 0;
	quote = 0;
	bak = m->status;
	m->status = 0;
	for (int i = 0; line[i] && !m->status; i++)
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
	if(m->status) {
		m->status = 1;
		return 1;
	}
	m->status = bak;
	return 0;
	
}

void	heredoc_count(char *line, int *cnt)
{
	int quote;

	quote = 0;
	for (int i = 0; line[i]; i++)
	{
		if (in_quote(line[i], &quote))
			continue ;
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
	shift_pipe(m);
	m->out[1] = old_out;
}
