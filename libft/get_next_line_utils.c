/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbokhari <sbokhari@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:01:51 by sbokhari          #+#    #+#             */
/*   Updated: 2022/08/08 18:01:58 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

size_t	ft_strlen_end(const char *str, char endl)
{
	size_t	count;

	count = 0;
	while (*str != '\0' && *str != endl)
	{
		str++;
		count++;
	}
	if (endl && *str == endl)
		count++;
	return (count);
}

t_fdlist	*ft_newlist_gnl(int fd, char *str)
{
	t_fdlist	*fdlist;
	int			len;

	fdlist = (t_fdlist *)malloc(sizeof(t_fdlist));
	if (!fdlist)
		return (NULL);
	fdlist->fd = fd;
	len = ft_strlen_end(str, 0);
	fdlist->str = malloc(len + 1);
	if (!(fdlist->str))
	{
		free(fdlist);
		return (NULL);
	}
	fdlist->str[len] = '\0';
	while (len--)
		fdlist->str[len] = str[len];
	fdlist->next = NULL;
	return (fdlist);
}

//Connects the previous list to the next and deletes the current
static void	ft_deletelist_gnl(char *str, t_fdlist **fdlist, int index)
{
	t_fdlist	*node;
	t_fdlist	*temp;

	free(str);
	if (!index)
	{
		temp = (*fdlist)->next;
		free(*fdlist);
		*fdlist = temp;
	}
	else
	{
		node = *fdlist;
		while (index > 1)
		{
			node = node->next;
			index--;
		}
		temp = node->next->next;
		free(node->next);
		node->next = temp;
	}
}

static int	ft_fdlistbuf_gnl(t_fdlist **fdlist, int index, char **fdstr,
		char **str)
{
	int		i;
	int		len2;
	int		len;
	char	*bakstr;

	len = ft_strlen_end(*fdstr, '\n');
	i = len;
	(*str)[len] = '\0';
	while (i--)
		(*str)[i] = (*fdstr)[i];
	len2 = ft_strlen_end(&((*fdstr)[len]), 0);
	if (len2)
	{
		bakstr = malloc(len2 + 1);
		if (!bakstr)
			return (-1);
		while (i++ < len2)
			bakstr[i] = (*fdstr)[len + i];
		free(*fdstr);
		*fdstr = bakstr;
	}
	else
		ft_deletelist_gnl(*fdstr, fdlist, index);
	return ((*str)[len - 1] == '\n');
}

int	ft_fdlistupdate_gnl(int fd, t_fdlist **fdlist, char **str)
{
	t_fdlist	*node;
	int			i;

	i = 0;
	node = *fdlist;
	while (node)
	{
		if (node->fd == fd)
		{
			if (node->str)
			{
				if (*str)
					free(*str);
				*str = malloc(ft_strlen_end(node->str, '\n') + 1);
				if (!*str)
					return (-1);
				return (ft_fdlistbuf_gnl(fdlist, i, &(node->str), str));
			}
			break ;
		}
		node = node->next;
		i++;
	}
	return (0);
}
