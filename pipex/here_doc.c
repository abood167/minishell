/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:58:04 by sbokhari          #+#    #+#             */
/*   Updated: 2022/12/14 14:45:05 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../minishell.h"

void	here_doc(t_mini *m, char *lim)
{
	char	*str;
	int		len[2];
	int		old_out;
	
	old_out = m->out[1];
	if (pipe(m->out) == -1)
		error_exit("Pipe: ");
	
	ft_lstadd_back(&m->pid, ft_lstnew((void*)(intptr_t)fork()));
	if (ft_lstlast(m->pid)->content == 0) {
		m->here_doc = 1;
		len[1] = ft_strlen(lim);
		while (1)
		{
			str = readline("> ");
			// str = get_next_line(0);
			if(str == NULL)
				exit(130);
				
			len[0] = ft_strlen(str);
			if (len[0] == len[1] && ft_strncmp(str, lim, len[0]) == 0)
				break;
			write(m->out[1], str, len[0]);
			write(m->out[1], "\n", 1);
			free(str);
		}
		free(str);
		close(m->out[1]);
		close(m->out[0]);
		exit(EXIT_SUCCESS);
	}
	close(m->out[1]);
	m->out[1] = old_out;
	m->in = m->out[0];
	wait_pipe(m);
	m->status = WEXITSTATUS(m->status);
	m->here_doc = 0;
}

void	cmdnotfound(char *cmd)
{
	write(2, "Command '", 9);
	while (*cmd)
		write(2, cmd++, 1);
	write(2, "' not found\n", 13);
}

void	filenotfound(char *file, int dir)
{
	write(2, "minishell: ", 11);
	while (*file)
		write(2, file++, 1);
	if (dir == 0)
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": Is a directory\n", 2);
}

void	error_exit(char *error)
{
	if (error == NULL)
		write(2, "Error: Invalid Number of Params\n", 33);
	else
	{
		write(2, "minishell: ", 7);
		perror(error);
	}
	exit(EXIT_FAILURE);
}