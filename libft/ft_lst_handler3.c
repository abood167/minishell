/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_handler3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbokhari <sbokhari@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 05:19:07 by sbokhari          #+#    #+#             */
/*   Updated: 2023/01/06 05:19:09 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (del)
		del(lst->content);
	free(lst);
}

void	ft_lstdelfirst(t_list **list, void (*del)(void *))
{
	t_list	*node;

	node = (*list)->next;
	if (del)
		del((*list)->content);
	free(*list);
	*list = node;
}

void	ft_lstdellast(t_list **list, void (*del)(void *))
{
	t_list	*node;

	if (!(*list)->next)
	{
		if (del)
			del((*list)->content);
		free(*list);
		*list = NULL;
		return ;
	}
	node = *list;
	while (node->next->next)
	{
		node = node->next;
	}
	if (del)
		del(node->next->content);
	free(node->next);
	node->next = NULL;
}
