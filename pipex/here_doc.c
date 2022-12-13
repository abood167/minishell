/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbokhari <sbokhari@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:58:04 by sbokhari          #+#    #+#             */
/*   Updated: 2022/12/12 15:58:20 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc(t_pipex *pipex, char *lim)
{
	char	*str;
	int		len[2];

	pipex->here_doc = 1;
	if (pipe(pipex->out) == -1)
		error_exit("Pipe: ");
	len[1] = ft_strlen(lim);
	while (1)
	{
		ft_printf("> ");
		str = get_next_line(0);
		len[0] = ft_strlen(str);
		if (len[0] - 1 == len[1] && ft_strncmp(str, lim, len[0] - 1) == 0)
			break;
		write(pipex->out[1], str, len[0]);
		free(str);
	}
	free(str);
	close(pipex->out[1]);
	pipex->in = pipex->out[0];
}

void	cmdnotfound(char *cmd)
{
	write(2, "Command '", 9);
	while (*cmd && *cmd != ' ')
		write(2, cmd++, 1);
	write(2, "' not found\n", 13);
}

void	filenotfound(char *file)
{
	write(2, "minishell: ", 11);
	while (*file && *file != ' ')
		write(2, file++, 1);
	write(2, ": No such file or directory\n", 29);
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
