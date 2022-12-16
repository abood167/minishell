#include "minishell.h"

void check_getenv(char **cmd)
{
	int i = 1;
	while (cmd[i])
	{

		if(getenv(cmd[i]) != NULL)
		{
			cmd[i] = getenv(cmd[i]);
		}
		i++;
	}
}

int check_digit(char *s)
{
	int i = 0;
	while(s[i] != '\0')
	{
		if(ft_isdigit(s[i]) == 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

// void get_get
void get_path(char **cmd)
{
	char *path;
	char *tmp;
	char **path_tab;
	int i = 0;

	path = getenv("PATH");
	path_tab = ft_split(path,':');
	while(path_tab[i])
	{
		tmp = ft_strjoin(path_tab[i],"/");
		tmp = ft_strjoin(tmp,cmd[0]);
		cmd[0] = tmp;
		i++;
	}
}


void print_env(char **cmd)
{
	int i = 0;
	while(cmd[i])
	{
		printf("%s\n",cmd[i]);
		i++;
	}
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



size_t	ft_strlcpyquote(char *dst, const char *src, size_t dstsize, int quote)
{
	size_t	i;
	size_t	j;

	if (!dstsize)
		return (ft_strlen(src));
	i = 0;
	j = 0;
	while (src[i] != '\0' && i < dstsize - 1)
	{
		if (src[i] == '\'' || src[i] == '\"')
		{
			if (quote == 0)
			{
				quote = src[i++];
				continue ;
			}
			else if (quote == src[i])
			{
				quote = 0;
				i++;
				continue ;
			}
		}
		dst[j] = src[i];
		i++;
		j++;
	}
	if (dstsize > 0)
		dst[j] = '\0';
	return (ft_strlen(src));
}

//used for split
char	*ft_substrquote(char const *s, unsigned int start, size_t len,
		int quote)
{
	char	*substr;
	size_t	i;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
		i = 0;
	else
	{
		i = ft_strlen(&s[start]);
		if (i > len)
			i = len;
	}
	substr = (char *)malloc(sizeof(char) * i + 1);
	if (!substr)
		return (NULL);
	ft_strlcpyquote(substr, &s[start], i + 1, quote);
	return (substr);
}

char	*ft_strchrquote(const char *s, int c, int quote)
{
	char	*a;
	int		i;

	i = 0;
	a = (char *)s;
	while (a[i])
	{
		if (quote > 0)
		{
			while (a[i] != quote)
				i++;
			return (&a[i]);
		}
		else if (quote < 0)
		{
			while (a[i] != -quote)
				i++;
			quote = 0;
		}
		if (a[i] == (char)c)
			return (&a[i]);
		i++;
	}
	if (a[i] == (char)c)
		return (&a[i]);
	return (NULL);
}