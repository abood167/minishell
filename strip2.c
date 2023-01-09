/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbokhari <sbokhari@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 05:41:17 by sbokhari          #+#    #+#             */
/*   Updated: 2023/01/06 05:41:23 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strip_heredoc(char *line, t_mini *m)
{
	int		quote;
	char	*word;
	int		bak;
	int		i;

	bak = m->status;
	init_zero(NULL, &quote, &m->status, &i);
	while (line[i] && !m->status)
	{
		if (!in_quote(line[i], &quote) && ft_strncmp(&line[i], "<<", 2) == 0)
		{
			i += 2;
			word = get_next_word(line, &i, ' ');
			here_doc(m, word);
			free(word);
			continue ;
		}
		i++;
	}
	if (m->status)
		return (1);
	m->status = bak;
	return (0);
}

void	heredoc_count(char *line, int *cnt)
{
	int	quote;
	int	i;

	quote = 0;
	i = 0;
	while (line[i])
	{
		if (in_quote(line[i], &quote))
			(void)NULL;
		else if (ft_strncmp(&line[i], "<<", 2) == 0)
		{
			i += 2;
			(*cnt)++;
		}
		i++;
	}
}

void	str_doc(t_mini *m)
{
	int	old_out;

	old_out = m->out[1];
	if (pipe(m->out) == -1)
		error_exit("Pipe: ");
	ft_putstr_fd(ft_lstindex(m->doc_str, m->here_doc++)->content, m->out[1]);
	write(m->out[1], "\0", 1);
	shift_pipe(m);
	m->out[1] = old_out;
}

int	in_brace(int *brace, char c)
{
	if (!*brace)
		return 0;
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
