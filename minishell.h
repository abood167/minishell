/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:55:17 by abin-saa          #+#    #+#             */
/*   Updated: 2023/01/11 12:48:53 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# if __linux__
#  define INC_EXIT 2
#  define CTRL_C_E 130
# else
#  define INC_EXIT 255
#  define CTRL_C_E 1
# endif

# define DEL_MSG "minishell: syntax error: unexpected end of file\nexit\n"

# include <sys/types.h>

# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft/libft.h"
# include "pipex/pipex.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <fnmatch.h>
# include <dirent.h>

//built in
void	echo_cmd(char **cmd, t_mini m);
void	cd_cmd(char **cmd, t_list *g_env, t_list *l_var);
void	print_env(void);

//env
char	**update_envp(t_list *list);
char	*get_var(char *varname, int len, t_list *g_env, t_list *l_var);
char	*set_var(char *line, t_list *g_env, t_list **l_var);
void	unset_var(char **cmd, t_list **g_env, t_list **l_var);
void	export_var(char **cmd, t_mini *m);
int		invalid_var(char *str, int set_var);
void	str_doc(t_mini *m);

//Arrays, list and strings
char	**ft_splitquote(char *s, char c);
t_list	*ft_split_shell(char *str, int mode, int brace, int pos);
char	*get_next_word(const char *str, int *pos, char c);
t_list	*ft_arrtolst(char **arr);
char	**ft_lsttoarr(t_list *list);
char	**ft_copyarr(char **arr);
void	printarr(char **list);
void	printlist(t_list *list);
char	*arrtostr(char **arr, int tofree);
char	*ft_lsttostr(t_list *arr);
void	sort_lst(t_list *g_env);
void	*init_zero(int *val1, int *val2, int *val3, int *val4);

//input modifiers
int		complete(char *oldline, t_mini *m);
int		shell_conditions(t_mini *m);
char	*pipe_shell(char *line, t_mini *m);
void	wait_pipe(t_mini *m);
char	*strip_redirect(char *line, t_mini *m, int test, int brace);
int		strip_heredoc(char *line, t_mini *m);
void	heredoc_count(char *line, int *cnt);
void	tr_doc(t_mini *m);
char	*ft_wildcard(char *line, DIR *dir);
char	*replace_withvar(char *str);

void	ft_int_signal(void);

t_mini	*get_mini(void);
int		in_quote(char c, int *quote);
int		in_brace(int *brace, char c);
int		has_pipe(char *line);
int		has_brace(char *line, t_mini *m);
int		invalid_syntax(char *str, t_mini *m);
void	syntax_error(char *str);
int		split_valid(t_list *split, char *oldline, int *val, int key);
int		bracket_invalid(char *str, int *val, t_mini *m);

int		alt_free(void *ptr, int ret);
int		alt_open(int *fd, char *file, int flag, int write);
void	alt_close(int *fd);
int		alt_pipe(int out[]);
void	shift_pipe(t_mini *m);

void	free_loop(void);
void	free_exit(void);
int		get_input(void);

#endif