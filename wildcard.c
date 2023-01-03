#include "minishell.h"

int	match_pattern(const char *pattern, const char *str, int *quote)
{
	int val;
	while (*pattern != '\0')
	{	
		val = in_quote(*pattern, quote);
		if(val == 1 || val == 2) {
			pattern++;
			continue;
		}
		// Handle wildcard characters in the pattern
		if (!*quote && *pattern == '*' && *str != '.')
		{
			// The "*" wildcard matches any sequence of characters
			pattern++;
			// Try to match the rest of the pattern with the remaining part of the string
			while (*str != '\0')
			{
				if (match_pattern(pattern, str, quote))
					return (1); // match found
				str++;
			}
			return (*pattern == '\0'); // match found if end of pattern reached
		} // Regular characters must match exactly
		else if (*pattern != *str)
			return (0); // no match
		pattern++;
		str++;
	}
	// Match found if end of pattern and string reached
	return (*pattern == '\0' && *str == '\0');
}

char	**ft_wildcard(char **line)
{
	t_list *list;
	int i;
	int flag;
	int quote;

	DIR *dir = opendir(".");
	struct dirent *entry;
	list = NULL;
	i = 0;
	while (line[i])
	{
		flag = 0;
		if (ft_strchr(line[i], '*'))
		{
			while ((entry = readdir(dir)) != NULL)
			{
				quote = 0;
				if (match_pattern(line[i], entry->d_name, &quote))
				{
					ft_lstadd_back(&list, ft_lstnew(ft_strdup(entry->d_name)));
					flag = 1;
				}
			}
			if (!flag)
				ft_lstadd_back(&list, ft_lstnew(ft_strdup(line[i])));
		}
		else
			ft_lstadd_back(&list, ft_lstnew(ft_strdup(line[i])));
		i++;
	}
	closedir(dir);
	ft_freearray((void**)line);
	line = ft_lsttoarr(list);
	ft_lstclear(&list, free);
	return (line);
}