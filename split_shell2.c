/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbokhari <sbokhari@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 05:39:52 by sbokhari          #+#    #+#             */
/*   Updated: 2023/01/06 05:40:09 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	complete(char *oldline, t_mini *m)
{
	int		bak;
	char	*str;

	bak = m->status;
	m->status = 0;
	rl_getc_function = getc;
	str = readline("> ");
	if (str == NULL)
	{
		if (!m->status)
		{
			ft_putstr_fd(DEL_MSG, 2); //confirm if same as mac //test for leaks
			free_loop();
			free_exit();
			exit(2);
		}
		free(m->line);
		m->line = NULL;
		rl_getc_function = rl_getc;
		return (1);
	}
	m->line = ft_strmerge(oldline, str);
	m->status = bak;
	rl_getc_function = rl_getc;
	return (2);
}

//Mode 2 = || &&
//Mode 1 = |
t_list	*ft_split_shell(char *str, int mode, int brace, int pos)
{
	t_list	*split;
	int		start;
	int		quote;

	split = init_zero(&pos, &start, &quote, NULL);
	while (str[pos])
	{
		if (in_quote(str[pos], &quote) || in_brace(&brace, str[pos]))
			(void)NULL;
		else if ((mode == 2 && !ft_strncmp(&str[pos], "&&", 2))
				|| !ft_strncmp(&str[pos], "||", mode))
		{
			if (pos - start > 0)
				ft_lstadd_back(&split, ft_lstnew(ft_substr(str, start, pos
								- start)));
			ft_lstadd_back(&split, ft_lstnew(ft_substr(str, pos, mode)));
			pos += mode;
			start = pos;
			continue ;
		}
		pos++;
	}
	if (pos - start > 0)
		ft_lstadd_back(&split, ft_lstnew(ft_strdup(&str[start])));
	return (split);
}
