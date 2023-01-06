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

int	match_pattern(const char *pattern, const char *str, int quote)
{
	int	val;

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
				if (match_pattern(pattern, str++, quote))
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

static void append_wspace(t_list **list, t_list *new){
	ft_lstadd_back(list, new);
	ft_lstadd_back(list, ft_lstnew(ft_strdup(" ")));
}

char	*ft_wildcard(char *line)
{
	t_list	*list;
	t_list	*entry;
	t_list	*node;
	int		i;
	int		j;
	int		flag;
	char	*word;
	DIR		*dir;

	dir = opendir(".");
	entry = get_dir_list(dir);
	list = NULL;
	i = 0;
	while (line[i])
	{
		flag = 0;
		while (line[i] == ' ')
			i++;
		j = i;
		word = get_next_word(line, &i, ' ');
		free(word);
		word = ft_substr(line, j, i - j);
		if (ft_strchr(word, '*'))
		{
			node = entry;
			while (node)
			{
				if (match_pattern(word, node->content, 0))
				{
					append_wspace(&list, ft_lstnew(ft_strdup(node->content)));
					flag = 1;
				}
				node = node->next;
			}
			if (!flag)
				append_wspace(&list, ft_lstnew(ft_strdup(word)));
		}
		else
			append_wspace(&list, ft_lstnew(ft_strdup(word)));
		free(word);
	}
	ft_lstclear(&entry, NULL);
	closedir(dir);
	free(line);
	line = ft_lsttostr(list);
	ft_lstclear(&list, free);
	return (line);
}
