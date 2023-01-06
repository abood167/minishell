/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:16:16 by sbokhari          #+#    #+#             */
/*   Updated: 2022/12/22 12:00:11 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "pipex.h"
#include <sys/stat.h>

char	*getcommand2(char **paths, char *cmd)
{
	char		*temp;
	char		*command;
	struct stat	path;

	while (*paths)
	{
		temp = ft_strjoin(*paths, "/");
		command = ft_strjoin(temp, cmd);
		free(temp);
		if (access(command, 0) == 0 && stat(command, &path) == 0
			&& S_ISREG(path.st_mode))
			return (command);
		free(command);
		paths++;
	}
	cmdnotfound(cmd);
	return (NULL);
}

char	*getcommand(char **paths, char *cmd, t_mini *m)
{
	struct stat	path;

	if (ft_strchr(cmd, '/') || !*paths)
	{
		if (access(cmd, 0) == 0)
		{
			stat(cmd, &path);
			if (S_ISREG(path.st_mode) == 0)
			{
				filenotfound(cmd, 1);
				m->status = 126;
				return (NULL);
			}
			return (ft_strdup(cmd));
		}
		filenotfound(cmd, 0);
		return (NULL);
	}
	return (getcommand2(paths, cmd));
}

void	child(t_mini m, char *argv[], char *envp[])
{
	m.status = 127;
	if (m.in != m.out[0])
		close(m.out[0]);
	dup2(m.in, STDIN_FILENO);
	dup2(m.out[1], STDOUT_FILENO);
	alt_close(&m.in);
	alt_close(&m.out[1]);
	m.args = argv;
	if (ft_strcmp(m.args[0], "exit") == 0)
		exit_command(&m);
	m.cmd = getcommand(m.paths, m.args[0], &m);
	if (!m.cmd)
	{
		child_free(&m);
		exit(m.status);
	}
	signal(SIGQUIT, m.slash_dfl);
	signal(SIGINT, m.ctrlc_dfl);
	execve(m.cmd, m.args, envp);
	ft_putstr_fd("minishell: ", 2);
	perror(m.cmd);
	child_free(&m);
	exit(126);
}

void	child_free(t_mini *m)
{
	if (m->args != m->cmds)
		ft_freearray((void **)m->args);
	free_loop();
	free_exit();
	free(m->cmd);
}
