/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbokhari <sbokhari@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:16:51 by sbokhari          #+#    #+#             */
/*   Updated: 2022/12/12 15:58:20 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		here_doc;
	int		in;
	int		is_child;
	pid_t	pid;
	int		out[2];
	char	*cmd;
	char	**paths;
	char	**args;
	int		status;
}			t_pipex;

void		pipex_init(t_pipex *pipex, char **envp);

void		child(t_pipex pipex, int pos, char *argv[], char *envp[]);
void		here_doc(t_pipex *pipex, char *lim);

void		parent_free(t_pipex *pipex);
void		child_free(t_pipex *pipex);

void		error_exit(char *err);
void		error_free(t_pipex *pipex, char *error);
void		cmdnotfound(char *cmd);
void		filenotfound(char *file, int dir);
void		writeline(char *str);

void		check_pipe(t_pipex *pipex);
void		exit_command(t_pipex *pipex);

#endif
