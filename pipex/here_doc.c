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

void	here_doc(t_pipex *pipex, char *lim)
{
	char	*str;
	int		len[2];
	int		old_out;
	
	old_out = pipex->out[1];
	if (pipe(pipex->out) == -1)
		error_exit("Pipe: ");
	
	pipex->pid = fork();
	if (pipex->pid == 0) {
		pipex->here_doc = 1;
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
			write(pipex->out[1], str, len[0]);
			write(pipex->out[1], "\n", 1);
			free(str);
		}
		free(str);
		close(pipex->out[1]);
		close(pipex->out[0]);
		exit(EXIT_SUCCESS);
	}
	close(pipex->out[1]);
	pipex->out[1] = old_out;
	pipex->in = pipex->out[0];
	waitpid(pipex->pid, &pipex->status, 0);
	pipex->status = WEXITSTATUS(pipex->status);
	pipex->here_doc = 0;
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
		write(2, "pipex: ", 7);
		perror(error);
	}
	exit(EXIT_FAILURE);
}

void	error_free(t_pipex *pipex, char *error)
{
	parent_free(pipex);
	error_exit(error);
}
