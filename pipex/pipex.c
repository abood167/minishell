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

void	shift_pipe(t_pipex *pipex, int i, char **argv, char **envp)
{
	int	status;

	pipex->pid = fork();
	if (pipex->pid == 0)
		child(*pipex, i, argv, envp);
	close(pipex->in);
	close(pipex->out[1]);
	pipex->in = pipex->out[0];
	waitpid(pipex->pid, &status, 0);
	pipex->status = WEXITSTATUS(status);
}

void	main2(t_pipex *pipex, char **argv, char **envp)
{
	int	i;

	i = 1 + pipex->here_doc;
	while (++i < pipex->argc - 1)
	{
		if (i != pipex->argc - 2)
		{
			if (pipe(pipex->out) == -1)
				error_free(pipex, "Pipe: ");
		}
		else
		{
			if (pipex->here_doc)
				pipex->out[1] = open(argv[pipex->argc - 1],
						O_CREAT | O_WRONLY | O_APPEND, 0644);
			else
				pipex->out[1] = open(argv[pipex->argc - 1],
						O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (pipex->out[1] < 0)
				error_free(pipex, argv[pipex->argc - 1]);
		}
		shift_pipe(pipex, i, argv, envp);
	}
	parent_free(pipex);
}

void	pipex_init(t_pipex *pipex, char **envp)
{
	char	**path;
	
	pipex->pid = 0;
	pipex->paths = NULL;
	pipex->here_doc = 0;
	// pipex->argc = argc;
	pipex->argc = 0;
	pipex->in = -1;
	pipex->out[1] = -1;
	// if (!ft_strcmp(argv[1], "here_doc"))
	// 	here_doc(pipex, argv);
	// else
	// 	pipex->in = open(argv[1], O_RDONLY);
	// if (pipex->in < 0)
	// 	error_exit(argv[1]);
	path = envp;
	//Handle failed to find path
	while (*path && ft_strncmp("PATH", *path, 4))
		path++;
	if (*path)
		pipex->paths = ft_split((*path + 5), ':');
	else
		pipex->paths = ft_split(" ", ' ');
	pipex->status = EXIT_SUCCESS;
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
