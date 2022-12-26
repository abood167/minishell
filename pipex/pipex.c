/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:16:25 by sbokhari          #+#    #+#             */
/*   Updated: 2022/12/22 16:07:26 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>

// void	shift_pipe(t_mini *m, int i, char **argv, char **envp)
// {
// 	int	status;

// 	m->pid = fork();
// 	if (m->pid == 0)
// 		child(*pipex, i, argv, envp);
// 	close(m->in);
// 	close(m->out[1]);
// 	m->in = m->out[0];
// 	waitpid(m->pid, &status, 0);
// 	m->status = WEXITSTATUS(status);
// }

void	pipex_init(t_mini *m, char **envp)
{
	char	**path;
	
	m->pid = NULL;
	m->paths = NULL;
	m->doc_str = NULL;
	m->here_doc = 0;
	m->in = -1;
	m->out[1] = -1;
	m->is_child = 0;
	path = envp;
	while (*path && ft_strncmp("PATH", *path, 4))
		path++;
	if (*path){
		m->paths = ft_split((*path + 5), ':');
	}
	else
		m->paths = ft_split(" ", ' ');
	m->cmd = NULL;
}

void check_pipe(t_mini *m) {
	if (m->in == -1)
		m->in = 0;
	if (m->out[1] == -1)
		m->out[1] = 1;
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_mini	pipex;

// 	if (argc < 5)
// 		error_exit(NULL);
// 	pipex_init(&m, argc, argv, envp);
// 	main2(&m, argv, envp);
// 	return (m.status);
// }
