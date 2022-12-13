/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbokhari <sbokhari@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:01:50 by sbokhari          #+#    #+#             */
/*   Updated: 2022/08/08 18:01:58 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

static int	ft_reallocate_gnl(char **str, size_t pos)
{
	size_t	i;
	char	*new;

	new = malloc(pos + BUFFER_SIZE + 1);
	if (!new)
	{
		free(*str);
		return (0);
	}
	if (*str)
	{
		i = 0;
		while (i < pos)
		{
			new[i] = (*str)[i];
			i++;
		}
		free(*str);
	}
	*str = new;
	return (1);
}

int	ft_contain_endl_gnl(char *str, int len, int status)
{
	int	i;

	i = 0;
	while (i < status)
	{
		if (str[len - i] == '\n' || str[len - i] <= 0)
			return (1);
		i++;
	}
	return (0);
}

static long long	ft_readline(char **str, int fd)
{
	size_t	i;
	ssize_t	status;

	i = 0;
	if (*str)
		i = ft_strlen_end(*str, 0);
	while (1)
	{
		if (!ft_reallocate_gnl(str, i))
			return (-1);
		status = read(fd, &(*str)[i], BUFFER_SIZE);
		if (status > 0)
			i += status;
		if (ft_contain_endl_gnl(*str, i - 1, status) || status <= 0)
		{
			if (i == 0)
				return (-1);
			if ((*str)[i - 1] != '\0')
				(*str)[i] = '\0';
			break ;
		}
	}
	return (1);
}

static char	*ft_split_gnl(int fd, t_fdlist **fdlist, char *str)
{
	int			len;
	t_fdlist	*node;
	char		*newstr;

	len = ft_strlen_end(str, '\n');
	if (str[len] == '\0')
		return (str);
	if (!*fdlist)
		*fdlist = ft_newlist_gnl(fd, &str[len]);
	else
	{
		node = *fdlist;
		while (node->next)
			node = node->next;
		node->next = ft_newlist_gnl(fd, &str[len]);
	}
	newstr = malloc(len + 1);
	if (newstr)
	{
		newstr[len] = '\0';
		while (len--)
			newstr[len] = str[len];
	}
	free(str);
	return (newstr);
}

char	*get_next_line(int fd)
{
	int				flag;
	char			*str;
	static t_fdlist	*fdlist;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = NULL;
	flag = ft_fdlistupdate_gnl(fd, &fdlist, &str);
	if (flag == 1)
		return (str);
	else if (flag == -1)
	{
		if (str)
			free(str);
		return (NULL);
	}
	if (ft_readline(&str, fd) < 0)
	{
		if (str)
			free(str);
		return (NULL);
	}
	return (ft_split_gnl(fd, &fdlist, str));
}
