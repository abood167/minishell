#include "minishell.h"

void	strip_heredoc(char *line, t_pipex *pipex)
{
	int len;
	int quote;
	char *word;

	len = 0;
	quote = 0;
	pipex->status = 0;
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
			here_doc(pipex, word); //handle error
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

void	str_doc(t_pipex *pipex)
{
	int		old_out;

	old_out = pipex->out[1];
	if (pipe(pipex->out) == -1)
		error_exit("Pipe: ");
	ft_putstr_fd(ft_lstindex(pipex->doc_str, pipex->here_doc++)->content, pipex->out[1]);
	write(pipex->out[1], "\0", 1);
	if (pipex->in != 0)
		close(pipex->in);
	close(pipex->out[1]);
	pipex->out[1] = old_out;
	pipex->in = pipex->out[0];
}
