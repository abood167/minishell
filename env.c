/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 05:39:35 by sbokhari          #+#    #+#             */
/*   Updated: 2023/01/06 11:17:43 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**update_envp(t_list *list)
{
	char	**arr;
	int		i;
	int		len;
	t_list	*node;

	node = list;
	len = 0;
	while (node)
	{
		if (ft_strchr((char *)node->content, '='))
			len++;
		node = node->next;
	}
	arr = (char **)malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (list)
	{
		if (ft_strchr((char *)list->content, '='))
			arr[i++] = ft_strdup((char *)list->content);
		list = list->next;
	}
	arr[i] = NULL;
	return (arr);
}

char	*get_var(char *varname, int len, t_list *g_env, t_list *l_var)
{
	if (strncmp(varname, "?", 1) == 0)
		return (ft_itoa(get_mini()->status));
	while (g_env)
	{
		if (strncmp(g_env->content, varname, len) == 0
			&& ((char *)g_env->content)[len] == '=')
			return (&((char *)g_env->content)[len + 1]);
		g_env = g_env->next;
	}
	while (l_var)
	{
		if (strncmp(l_var->content, varname, len) == 0
			&& ((char *)l_var->content)[len] == '=')
			return (&((char *)l_var->content)[len + 1]);
		l_var = l_var->next;
	}
	return (NULL);
}


void	unset_var(char **cmd, t_list **g_env, t_list **l_var)
{
	int		i;
	int		len;
	t_list	*g_point;
	t_list	*l_point;
	t_list	*prev;

	i = 0;
	while (cmd[i])
	{
		len = ft_strlen(cmd[i]);
		g_point = *g_env;
		while (g_point)
		{
			if (strncmp(g_point->content, cmd[i], len) == 0
				&& (((char *)g_point->content)[len] == '='
					|| !((char *)g_point->content)[len]))
			{
				if (g_point == *g_env)
					*g_env = (*g_env)->next;
				else
					prev->next = g_point->next;
				free(g_point->content);
				free(g_point);
				break ;
			}
			prev = g_point;
			g_point = g_point->next;
		}
		l_point = *l_var;
		while (l_point)
		{
			if (strncmp(l_point->content, cmd[i], len) == 0
				&& ((char *)l_point->content)[len] == '=')
			{
				if (l_point == *l_var)
					*l_var = (*l_var)->next;
				else
					prev->next = l_point->next;
				free(l_point->content);
				free(l_point);
				break ;
			}
			prev = l_point;
			l_point = l_point->next;
		}
		i++;
	}
}