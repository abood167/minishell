/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:58:04 by sbokhari          #+#    #+#             */
/*   Updated: 2022/12/14 14:45:05 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../minishell.h"

void	here_doc(t_mini *m, char *lim)
{
	char	*str;
	int		len[2];
	t_list  *node;
	rl_getc_func_t *bak;
	
	ft_lstadd_back(&m->doc_str, ft_lstnew(strdup("")));
	node = ft_lstlast(m->doc_str);
	bak = rl_getc_function;
	rl_getc_function = getc;
	len[1] = ft_strlen(lim);
	while (1)
	{
		str = readline("> ");
		// str = get_next_line(0);
		if(str == NULL){
			rl_getc_function = bak;
			return;
		}
		len[0] = ft_strlen(str);
		if (len[0] == len[1] && ft_strncmp(str, lim, len[0]) == 0)
			break;
		node->content = ft_strmerge(node->content, str);
		node->content = ft_strjoin(node->content, ft_strdup("\n"));
	}
	rl_getc_function = bak;
}

void	cmdnotfound(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	while (*cmd)
		write(2, cmd++, 1);
	ft_putstr_fd(": command not found\n", 2);
}

void	filenotfound(char *file, int dir)
{
	write(2, "minishell: ", 11);
	while (*file)
		write(2, file++, 1);
	if (dir == 0)
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": Is a directory\n", 2);
}

void	error_exit(char *error)
{
	if (error == NULL)
		write(2, "Error: Invalid Number of Params\n", 33);
	else
	{
		write(2, "minishell: ", 7);
		perror(error);
	}
	exit(EXIT_FAILURE);
}