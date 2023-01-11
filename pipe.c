/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 05:39:36 by sbokhari          #+#    #+#             */
/*   Updated: 2023/01/10 08:34:21 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_pipe(t_mini *m)
{
	t_list	*node;
	int		status;

	node = m->pid;
	while (node)
	{
		waitpid((pid_t)(intptr_t)node->content, &status, 0);
		m->status = WEXITSTATUS(status);
		node = node->next;
	}
	ft_lstclear(&m->pid, NULL);
}

int	has_pipe(char *line)
{
	t_list	*pipe_line;
	int		val;

	pipe_line = ft_split_shell(line, 1, 1, 0);
	val = ft_lstsize(pipe_line);
	ft_lstclear(&pipe_line, free);
	if (val >= 2)
		return (1);
	return (0);
}

int	start_pipe(t_mini *m)
{
	ft_lstadd_back(&m->pid, ft_lstnew((void *)(intptr_t)fork()));
	if (ft_lstlast(m->pid)->content == 0)
	{
		ft_lstclear(&m->buffer, free);
		m->is_child = 1;
		if (m->in != m->out[0])
			alt_close(&m->out[0]);
		dup2(m->in, STDIN_FILENO);
		dup2(m->out[1], STDOUT_FILENO);
		return (1);
	}
	shift_pipe(m);
	return (0);
}

char	*pipe_shell(char *line, t_mini *m)
{
	t_list	*pipe_line;
	t_list	*start;

	pipe_line = ft_split_shell(line, 1, 1, 0);
	start = pipe_line;
	line = (void *)(intptr_t)alt_free(line, 0);
	while (pipe_line)
	{
		if (((char *)pipe_line->content)[0] == '|')
			pipe_line = pipe_line->next;
		if (pipe_line->next)
			alt_pipe(m->out);
		if (start_pipe(m))
			break ;
		heredoc_count(pipe_line->content, &m->here_doc);
		pipe_line = pipe_line->next;
	}
	if (pipe_line)
		line = ft_strdup((char *)pipe_line->content);
	ft_lstclear(&start, free);
	if (ft_lstlast(m->pid)->content != 0)
		wait_pipe(m);
	return (line);
}
