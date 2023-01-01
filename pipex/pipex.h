/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m.h                                            :+:      :+:    :+:   */
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

typedef struct s_mini
{
	t_list  *doc_str;
	int		here_doc;
	int		in;
	int		is_child;
	t_list	*pid;
	int		out[2];
	char	*cmd;
	char	**paths;
	char	**args;
	int		status;
	
	char	**cmds;
	char	*line;
	char	**envp;
	t_list 	*g_env;
	t_list	*l_var;
}			t_mini;

void		mini_init(t_mini *m, char **envp);

void		child(t_mini m, char *argv[], char *envp[]);
void		here_doc(t_mini *m, char *lim);

void		child_free(t_mini *m);

void		error_exit(char *err);
void		cmdnotfound(char *cmd);
void		filenotfound(char *file, int dir);
void		writeline(char *str);

void		check_pipe(t_mini *m);
void		exit_command(t_mini *m);

#endif
