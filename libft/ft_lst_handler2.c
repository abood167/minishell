/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_handler2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbokhari <sbokhari@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:05:51 by sbokhari          #+#    #+#             */
/*   Updated: 2022/07/17 16:05:58 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*start;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	start = node;
	while (lst)
	{
		node->content = f(lst->content);
		lst = lst->next;
		node->next = NULL;
		if (lst)
		{
			node->next = (t_list *)malloc(sizeof(t_list));
			if (!node->next)
			{
				ft_lstclear(&start, del);
				return (NULL);
			}
			node = node->next;
		}
	}
	return (start);
}
