#include "minshell.h"

void	printarr(char **arr)
{
	while (*arr)
	{
		printf("%s\n", *arr);
		arr++;
	}
}

void	printlist(t_list *list)
{
	while (list)
	{
		printf("%s\n", (char *)list->content);
		list = list->next;
	}
}

t_list	*ft_arrtolst(char **arr)
{
	t_list	*list;

	list = NULL;
	while (*arr)
	{
		ft_lstadd_back(&list, ft_lstnew((void *)ft_strdup(*arr)));
		arr++;
	}
	return (list);
}

char	**ft_lsttoarr(t_list *list)
{
	char	**arr;
	int		i;

	arr = (char **)malloc(sizeof(char *) * (ft_lstsize(list) + 1));
	i = 0;
	while (list)
	{
		arr[i++] = ft_strdup((char *)list->content);
		list = list->next;
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_copyarr(char **arr)
{
	char	**copy;
	int		len;

	len = ft_2dlen((void **)arr);
	copy = (char **)malloc(sizeof(char *) * (len + 1));
	copy[len] = NULL;
	while (len--)
		copy[len] = strdup(arr[len]);
	return (copy);
}

int	in_quote(char c, int *quote)
{
	if (c == '\'' || c == '\"')
	{
		if (c == *quote)
		{
			*quote = 0;
			return (1); //close
		}
		else if (!*quote)
		{
			*quote = c;
			return (2); //open
		}
	}
	else if (*quote)
		return (3); //ingore quote
	return (0);     //not in quote
}

int	split_len(char *str, char *split)
{
	int	len;
	int	split_pos;

	len = 0;
	split_pos = 0;
	while (split[split_pos])
	{
		if (split[split_pos] == str[len])
			split_pos++;
		len++;
	}
	if (str[len] == '\'' || str[len] == '\"')
		len++;
	return (len);
}

char	*listtostr(t_list *arr)
{
	char	*str;
	int		len;
	t_list	*start;

	len = 0;
	start = arr;
	while (arr)
	{
		len += ft_strlen((char *)arr->content);
		arr = arr->next;
	}
	str = (char *)malloc(sizeof(char) * (len + 1));
	str[len] = '\0';
	len = 0;
	while (start)
	{
		ft_strcpy(&str[len], (char *)start->content);
		len += ft_strlen((char *)start->content);
		start = start->next;
	}
	return (str);
}

char	*arrtostr(char **arr)
{
	char	*str;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (arr[i])
	{
		len += ft_strlen(arr[i]);
		i++;
	}
	str = (char *)malloc(sizeof(char) * (len + 1));
	str[len] = '\0';
	i = 0;
	len = 0;
	while (arr[i])
	{
		ft_strcpy(&str[len], arr[i]);
		len += ft_strlen(arr[i]);
		i++;
	}
	return (str);
}

char	*get_next_word(const char *str, int *pos, char c)
{
	int		quote;
	int		start;
	int		count;
	char	**words;
	char	*line;

	quote = 0;
	count = 0;
	while (str[*pos] && str[*pos] == c)
		(*pos)++;
	if (!str[*pos])
		return (NULL);
	start = *pos;
	while (str[*pos] && (str[*pos] != c || quote))
	{
		if (in_quote(str[*pos], &quote) == 2)
			count++;
		else if (*pos - start == 0)
			count++;
		else if (!quote && *pos - start && in_quote(str[*pos - 1], &quote))
		{
			quote = 0;
			count++;
		}
		(*pos)++;
	}
	if (quote)
		return (NULL); //Quotes did not close
	words = (char **)malloc(sizeof(char *) * (count + 1));
	*pos = start;
	count = 0;
	while (str[*pos] && str[*pos] != c)
	{
		start = *pos;
		if (in_quote(str[*pos], &quote) == 2)
		{
			start = ++(*pos);
			while (in_quote(str[*pos], &quote) != 1)
				(*pos)++;
			words[count++] = ft_substr(str, start, *pos - start);
			(*pos)++;
		}
		else
		{
			while (str[*pos] && str[*pos] != c && !in_quote(str[*pos], &quote))
				(*pos)++;
			words[count++] = ft_substr(str, start, *pos - start);
			if (quote)
				quote = 0;
		}
	}
	words[count] = NULL;
	line = arrtostr(words);
	ft_freearray((void **)words);
	return (line);
}
