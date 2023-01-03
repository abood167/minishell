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
void echo_cmd(char **cmd, t_mini m);
void cd_cmd(char **cmd, t_list *g_env, t_list *l_var);
void print_env();

//env
char	**update_envp(t_list *list);
char*   get_var(char *varname, int len, t_list *g_env, t_list *l_var);
char* set_var(char *line, t_list *g_env, t_list **l_var);
void unset_var(char **cmd, t_list **g_env, t_list **l_var);
void export_var(char **cmd, t_list **g_env, t_list **l_var);

//Arrays, list and strings
char**  ft_splitquote(char *s, char c);
t_list*	ft_split_shell(char *str, int mode, int brace);
char* get_next_word(const char *str, int *pos, char c);
t_list* ft_arrtolst(char **arr);
char** ft_lsttoarr(t_list *list);
char** ft_copyarr(char **arr);
void    printarr(char **list);
void    printlist(t_list *list);
char* arrtostr(char **arr);
char* listtostr(t_list *arr);

//input modifiers
int shell_conditions(t_mini *m);
char	*pipe_shell(char *line, t_mini *m);
void	wait_pipe(t_mini *m);
char*   strip_redirect(char *line, t_mini *m, int test);
int	strip_heredoc(char *line, t_mini *m);
void     heredoc_count(char *line, int *cnt);
void    str_doc(t_mini *m);
char** ft_wildcard(char **line);

void ft_int_signal();
t_mini* get_mini();
int in_quote(char c, int *quote);
int has_pipe(char *line);
int pipe_brace(char *line, t_mini *m);
int invalid_syntax(char *str, t_mini *m);
void syntax_error(char *str);

int alt_open(int *fd, char *file, int flag, int write);
void alt_close(int *fd);
int alt_pipe(int out[]);
void	shift_pipe(t_mini *m);

void free_loop();
void free_exit();

#endif