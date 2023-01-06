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
#include "../minishell.h"
#include <sys/wait.h>

int		has_brace(char *line, t_mini *m);

void	fix_dir(void)
{
	char	*line;

	line = getcwd(NULL, 0);
	while (!line)
	{
		cd_cmd(ft_split("cd ..", ' '), NULL, NULL); //Not like bash
		free(line);
		line = getcwd(NULL, 0);
	}
	free(line);
}

void	mini_init(t_mini *m)
{
	char	**path;

	m->start = 0;
	m->envp = update_envp(m->g_env);
	m->pid = NULL;
	m->paths = NULL;
	if (m->doc_str == NULL)
		m->here_doc = 0;
	else if (m->here_doc == ft_lstsize(m->doc_str))
	{
		ft_lstclear(&m->doc_str, free);
		m->here_doc = 0;
	}
	m->in = 0;
	m->out[1] = 1;
	path = m->envp;
	while (*path && ft_strncmp("PATH", *path, 4))
		path++;
	if (*path)
		m->paths = ft_split((*path + 5), ':');
	else
		m->paths = ft_split(" ", ' ');
	m->line = NULL;
	m->cmd = NULL;
	fix_dir();
}

void	check_pipe(t_mini *m)
{
	if (m->in == -1)
		m->in = 0;
	if (m->out[1] == -1)
		m->out[1] = 1;
}
