/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbokhari <sbokhari@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 05:39:34 by sbokhari          #+#    #+#             */
/*   Updated: 2023/01/06 05:39:57 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_brace_block(char *line)
{
	char	*lcopy;
	int		brace;
	int		i;

	lcopy = strip_redirect(ft_strdup(line), get_mini(), 1, 1);
	i = 0;
	while (lcopy[i] == ' ' || lcopy[i] == '\n')
		i++;
	if (lcopy[i++] != '(')
		return (alt_free(lcopy, 0));
	brace = 1;
	while (lcopy[i] && brace)
	{
		if (lcopy[i] == ')')
			brace--;
		else if (lcopy[i] == '(')
			brace++;
		i++;
	}
	while (lcopy[i] == ' ' || lcopy[i] == '\n')
		i++;
	if (!lcopy[i])
		return (alt_free(lcopy, 1));
	return (alt_free(lcopy, 0));
}

int	has_brace(char *line, t_mini *m)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '(')
	{
		if (m)
		{
			m->buffer = ft_lstnew(line);
			m->line = NULL;
		}
		return (1);
	}
	return (0);
}

static char	*brace_peel(char *line)
{
	unsigned int	start;
	unsigned int	end;

	start = 0;
	while (line[start] != '(')
		start++;
	start++;
	end = ft_strlen(line) - 1;
	while (line[end] != ')')
		end--;
	end -= start;
	return (ft_substr(line, start, end));
}

int	shell_conditions2(t_mini *m)
{
	pid_t	pid;

	if (is_brace_block((char *)m->buffer->content))
	{
		pid = fork();
		if (pid == 0)
		{
			m->is_child = 1;
			m->buffer->content = strip_redirect(m->buffer->content, m, 0, 1);
			m->line = brace_peel(m->buffer->content);
			dup2(m->in, STDIN_FILENO);
			dup2(m->out[1], STDOUT_FILENO);
			ft_lstclear(&m->buffer, free);
			return (shell_conditions(m));
		}
		heredoc_count((char *)m->buffer->content, &m->here_doc);
		waitpid(pid, &m->status, 0);
		m->status = WEXITSTATUS(m->status);
		ft_lstdelfirst(&m->buffer, free);
		return (1);
	}
	m->line = (char *)m->buffer->content;
	ft_lstdelfirst(&m->buffer, NULL);
	return (0);
}

int	shell_conditions(t_mini *m)
{
	if (m->line)
	{
		m->buffer = ft_split_shell(m->line, 2, 1, 0);
		free(m->line);
		m->line = NULL;
	}
	if (!ft_strcmp((char *)m->buffer->content, "&&"))
	{
		ft_lstdelfirst(&m->buffer, free);
		if (m->status)
			ft_lstdelfirst(&m->buffer, free);
		return (1);
	}
	else if (!ft_strcmp((char *)m->buffer->content, "||"))
	{
		ft_lstdelfirst(&m->buffer, free);
		if (!m->status)
			ft_lstdelfirst(&m->buffer, free);
		return (1);
	}
	return (shell_conditions2(m));
}
