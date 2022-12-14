/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:16:16 by sbokhari          #+#    #+#             */
/*   Updated: 2022/12/14 11:26:36 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*getcommand(char **paths, char *cmd)
{
	char	*temp;
	char	*command;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, 0) == 0)
			return (cmd);
		filenotfound(cmd);
		return NULL;
	}


	while (*paths)
	{
		temp = ft_strjoin(*paths, "/");
		command = ft_strjoin(temp, cmd);
		free(temp);
		if (access(command, 0) == 0)
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
		exit(EXIT_FAILURE);
	}
	execve(pipex.cmd, pipex.args, envp);
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
