/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbokhari <sbokhari@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 05:41:15 by sbokhari          #+#    #+#             */
/*   Updated: 2023/01/06 05:41:23 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	match_pattern(const char *pattern, const char *str, int quote, int val)
{
	while (*pattern != '\0')
	{
		val = in_quote(*pattern, &quote);
		if (val == 1 || val == 2)
		{
			pattern++;
			continue ;
		}
		if (!quote && *pattern == '*' && *str != '.')
		{
			pattern++;
			while (*str != '\0')
			{
				if (match_pattern(pattern, str++, quote, 0))
					return (1);
			}
			return (*pattern == '\0');
		}
		else if (*pattern != *str)
			return (0);
		pattern++;
		str++;
	}
	return (*pattern == '\0' && *str == '\0');
}

t_list	*get_dir_list(DIR *dir)
{
	t_list			*list;
	struct dirent	*entry;

	list = NULL;
	entry = readdir(dir);
	while (entry)
	{
		ft_lstadd_front(&list, ft_lstnew(entry->d_name));
		entry = readdir(dir);
	}
	sort_lst(list);
	return (list);
}

static void	append_wspace(t_list **list, t_list *new)
{
	ft_lstadd_back(list, new);
	ft_lstadd_back(list, ft_lstnew(ft_strdup(" ")));
}

void ft_wildcard2(char *word, int flag, t_list *list[])
{
	list[2] = list[1];
	while (list[2])
	{
		if (match_pattern(word, list[2]->content, 0, 0))
		{
			append_wspace(&list[0], ft_lstnew(ft_strdup(list[2]->content)));
			flag = 1;
		}
		list[2] = list[2]->next;
	}
	if (!flag)
		append_wspace(&list[0], ft_lstnew(ft_strdup(word)));
}

char	*ft_wildcard(char *line, DIR *dir)
{
	t_list	*list[3];
	int		i;
	int		j;
	char	*word;

	list[1] = get_dir_list(dir);
	list[0] = init_zero(&i, &j, NULL, NULL);
	while (line[i])
	{
		while (line[i] == ' ')
			j = ++i;
		free(get_next_word(line, &i, ' '));
		word = ft_substr(line, j, i - j);
		if (ft_strchr(word, '*'))
			ft_wildcard2(word, 0, list);
		else
			append_wspace(&list[0], ft_lstnew(ft_strdup(word)));
		free(word);
	}
	ft_lstclear(&list[1], NULL);
	closedir(dir);
	free(line);
	line = ft_lsttostr(list[0]);
	ft_lstclear(&list[0], free);
	return (line);
}
