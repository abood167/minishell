/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:55:17 by abin-saa          #+#    #+#             */
/*   Updated: 2022/12/15 11:18:10 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

//built in
void echo_cmd(char **cmd, t_pipex pipex);
void cd_cmd(char **cmd, t_list *g_env, t_list *l_var);

//env
char*   get_var(char *varname, int len, t_list *g_env, t_list *l_var);
char* set_var(char *line, t_list *g_env, t_list **l_var);
void unset_var(char **cmd, t_list **g_env, t_list **l_var);
void export_var(char **cmd, t_list **g_env, t_list **l_var);

//Arrays, list and strings
char**  ft_splitquote(char *s, char c);
t_list*	ft_split_shell(char *str, int mode);
char* get_next_word(const char *str, int *pos, char c);
t_list* ft_arrtolst(char **arr);
char** ft_lsttoarr(t_list *list);
char** ft_copyarr(char **arr);
void    printarr(char **list);
void    printlist(t_list *list);
char* arrtostr(char **arr);
char* listtostr(t_list *arr);

//input modifiers
char	*pipe_shell(char *line, t_pipex *pipex);
void	wait_pipe(t_pipex *pipex);
char*   strip_redirect(char *line, t_pipex *pipex, int test);
char** ft_wildcard(char **line);

void ft_int_signal();
t_pipex* get_pipex();
int in_quote(char c, int *quote);
int invalid_syntax(char *str, t_pipex *pipex);
void syntax_error(char *str);

#endif