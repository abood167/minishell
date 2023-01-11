/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 08:51:49 by abin-saa          #+#    #+#             */
/*   Updated: 2023/01/10 08:52:10 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		copy[len] = ft_strdup(arr[len]);
	return (copy);
}
