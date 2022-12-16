/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minshell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:55:17 by abin-saa          #+#    #+#             */
/*   Updated: 2022/12/15 11:18:10 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINSHELL_H
# define MINSHELL_H

#include <sys/types.h>

#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"
#include "pipex/pipex.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <fnmatch.h>
#include <dirent.h>

char	**ft_splitquote(char *s, char c);
void    printarr(char **list);
void    printlist(t_list *list);
char*   strip_redirect(char *line, t_pipex *pipex);

t_list* ft_arrtolst(char **arr);
char** ft_lsttoarr(t_list *list);
char **ft_copyarr(char **arr);

char* set_var(char *line, t_list *g_env, t_list **l_var);
void unset_var(char **cmd, t_list **g_env, t_list **l_var);
char** ft_wildcard(char **line);

int in_quote(char c, int *quote);
char* get_next_word(const char *str, int *pos, char c);
int split_len(char *str, char *split);
char* arrtostr(char **arr);
char* listtostr(t_list *arr);

int get_status();

char	*pipe_shell(char *line, t_pipex *pipex);

#endif