/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbokhari <sbokhari@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:05:50 by sbokhari          #+#    #+#             */
/*   Updated: 2022/07/17 16:05:56 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*node;

	node = *lst;
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new;
	}
	else
	{
		*lst = new;
	}
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if(del)
		del(lst->content);
	free(lst);
}

void ft_lstdelfirst(t_list **list, void (*del)(void *)) {
    t_list *node;
    
    node = (*list)->next;
	if (del)
		del((*list)->content);
    free(*list);
    *list = node;
}

void ft_lstdellast(t_list **list, void (*del)(void *)) {
    t_list *node;
    
    if(!(*list)->next) {
		if (del)
			del((*list)->content);
        free(*list);
        *list = NULL;
        return;
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

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if(*lst) {
		if ((*lst)->next)
			ft_lstclear(&(*lst)->next, del);
		if(del)
			del((*lst)->content);
		free(*lst);
		*lst = NULL;
	}
}
