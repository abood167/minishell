#include "minishell.h"

int	match_pattern(const char *pattern, const char *str, int quote)
{
	int val;
	while (*pattern != '\0')
	{	
		val = in_quote(*pattern, &quote);
		if(val == 1 || val == 2) {
			pattern++;
			continue;
		}
		if (!quote && *pattern == '*' && *str != '.')
		{
			pattern++;
			while (*str != '\0')
			{
				if (match_pattern(pattern, str, quote))
					return (1);
				str++;
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

char	*ft_wildcard(char *line)
{
	t_list *list;
	int i;
	int j;
	int flag;
	char *word;

	DIR *dir = opendir(".");
	struct dirent *entry;
	list = NULL;
	i = 0;
	while (line[i])
	{
		flag = 0;
		while(line[i] == ' ')
			i++;
		j = i;
		word = get_next_word(line, &i, ' ');
		free(word);
		word = ft_substr(line, j, i - j);
		if (ft_strchr(word, '*'))
		{
			while ((entry = readdir(dir)) != NULL)
			{
				if (match_pattern(word, entry->d_name, 0))
				{
					ft_lstadd_back(&list, ft_lstnew(ft_strdup(entry->d_name)));
					ft_lstadd_back(&list, ft_lstnew(ft_strdup(" ")));
					flag = 1;
				}
			}
			if (!flag) {
				ft_lstadd_back(&list, ft_lstnew(ft_strdup(word)));
				ft_lstadd_back(&list, ft_lstnew(ft_strdup(" ")));
			}
		}
		else
		{
			ft_lstadd_back(&list, ft_lstnew(ft_strdup(word)));
			ft_lstadd_back(&list, ft_lstnew(ft_strdup(" ")));
		}
		free(word);
	}
	closedir(dir);
	free(line);
	line = ft_lsttostr(list);
	ft_lstclear(&list, free);
	return (line);
}