/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:16:25 by sbokhari          #+#    #+#             */
/*   Updated: 2022/12/14 15:49:19 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>

// void	shift_pipe(t_pipex *pipex, int i, char **argv, char **envp)
// {
// 	int	status;

// 	pipex->pid = fork();
// 	if (pipex->pid == 0)
// 		child(*pipex, i, argv, envp);
// 	close(pipex->in);
// 	close(pipex->out[1]);
// 	pipex->in = pipex->out[0];
// 	waitpid(pipex->pid, &status, 0);
// 	pipex->status = WEXITSTATUS(status);
// }

void	pipex_init(t_pipex *pipex, char **envp)
{
	char	**path;
	
	pipex->pid = NULL;
	pipex->paths = NULL;
	pipex->here_doc = 0;
	pipex->in = -1;
	pipex->out[1] = -1;
	pipex->is_child = 0;
	path = envp;
	while (*path && ft_strncmp("PATH", *path, 4))
		path++;
	if (*path)
		pipex->paths = ft_split((*path + 5), ':');
	else
		pipex->paths = ft_split(" ", ' ');
	pipex->cmd = NULL;
}

void check_pipe(t_pipex *pipex) {
	if (pipex->in == -1)
		pipex->in = 0;
	if (pipex->out[1] == -1)
		pipex->out[1] = 1;
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_pipex	pipex;

// 	if (argc < 5)
// 		error_exit(NULL);
// 	pipex_init(&pipex, argc, argv, envp);
// 	main2(&pipex, argv, envp);
// 	return (pipex.status);
// }
