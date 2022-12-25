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

#include "pipex.h"
#include <sys/stat.h>

char	*getcommand(char **paths, char *cmd)
{
	char	*temp;
	char	*command;
	struct stat path;

	if (ft_strchr(cmd, '/') || !*paths)
	{
		if (access(cmd, 0) == 0)
		{
			stat(cmd, &path);
			if(S_ISREG(path.st_mode) == 0) {
				filenotfound(cmd, 1);
				return NULL;
			}
			return (cmd);
		}
		filenotfound(cmd, 0);
		return NULL;
	}

	while (*paths)
	{
		temp = ft_strjoin(*paths, "/");
		command = ft_strjoin(temp, cmd);
		free(temp);
		if (access(command, 0) == 0 && stat(command, &path) == 0 && S_ISREG(path.st_mode))
			return (command);
		free(command);
		paths++;
	}
	cmdnotfound(cmd);
	return (NULL);
}

void	exit_command(t_pipex *pipex)
{
	int	exit_code;

	// ft_putstr_fd("exit\n", 2);
	if (ft_2dlen((void **)pipex->args) == 1)
	{
		child_free(pipex);
		exit(1);
	}
	else if (!ft_isstrdigit(pipex->args[1]))
	{
		write(2, "pipex: exit: ", 13);
		write(2, pipex->args[1], ft_strlen(pipex->args[1]));
		write(2, ": numeric argument required\n", 29);
		child_free(pipex);
		exit(2);
	}
	else if (ft_2dlen((void **)pipex->args) > 2)
	{
		write(2, "pipex: exit: too many arguments\n", 33);
		child_free(pipex);
		exit(1);
	}
	exit_code = atoi(pipex->args[1]);
	child_free(pipex);
	exit(exit_code);
}

void	child(t_pipex pipex, int pos, char *argv[], char *envp[])
{
	if (pos == 2 + pipex.here_doc)
		close(pipex.out[0]);
	dup2(pipex.in, STDIN_FILENO);
	dup2(pipex.out[1], STDOUT_FILENO);
	pipex.args = argv;
	if (ft_strcmp(pipex.args[0], "exit") == 0)
		exit_command(&pipex);
	pipex.cmd = getcommand(pipex.paths, pipex.args[0]);
	if (!pipex.cmd)
	{
		child_free(&pipex);
		exit(127);
	}
	if(execve(pipex.cmd, pipex.args, envp))
	{
		ft_putstr_fd("minishell: " , 2);
		ft_putstr_fd(pipex.cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		child_free(&pipex);
		parent_free(&pipex);
		exit(126);
	}
	parent_free(&pipex);
}

void	parent_free(t_pipex *pipex)
{
	close(pipex->in);
	close(pipex->out[0]);
	close(pipex->out[1]);
	ft_freearray((void **)pipex->paths);
}

void	child_free(t_pipex *pipex)
{
	ft_freearray((void **)pipex->args);
	free(pipex->cmd);
}
