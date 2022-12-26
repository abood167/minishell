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
#include "../minishell.h"
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

void	exit_command(t_mini *m)
{
	int	exit_code;

	// ft_putstr_fd("exit\n", 2);
	if (ft_2dlen((void **)m->args) == 1)
	{
		child_free(m);
		exit(1);
	}
	else if (!ft_isstrdigit(m->args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		write(2, m->args[1], ft_strlen(m->args[1]));
		write(2, ": numeric argument required\n", 29);
		child_free(m);
		exit(2);
	}
	else if (ft_2dlen((void **)m->args) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		child_free(m);
		exit(1);
	}
	exit_code = atoi(m->args[1]);
	child_free(m);
	exit(exit_code);
}

void	child(t_mini m, char *argv[], char *envp[])
{
	if (m.in != m.out[0])
		close(m.out[0]);
	dup2(m.in, STDIN_FILENO);
	dup2(m.out[1], STDOUT_FILENO);
	m.args = argv;
	if (ft_strcmp(m.args[0], "exit") == 0)
		exit_command(&m);
	m.cmd = getcommand(m.paths, m.args[0]);
	if (!m.cmd)
	{
		child_free(&m);
		exit(127);
	}
	if(execve(m.cmd, m.args, envp))
	{
		ft_putstr_fd("minishell: " , 2);
		ft_putstr_fd(m.cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		child_free(&m);
		exit(126);
	}
}

void	parent_free(t_mini *m)
{
	free_loop();
	free_exit();
	close(m->in);
	close(m->out[0]);
	close(m->out[1]);
}

void	child_free(t_mini *m)
{
	if (m->args != m->cmds)
		ft_freearray((void **)m->args);
	free_loop();
	free_exit();
	free(m->cmd);
}
