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

int	update_var(char *var, t_list *g_env)
{
	size_t	len;

	len = (size_t)ft_strchr(var, '=') - (size_t)var;
	while (g_env)
	{
		if (!ft_strncmp((char *)g_env->content, var, len + 1))
		{
			free(g_env->content);
			g_env->content = var;
			return (1);
		}
		g_env = g_env->next;
	}
	return (0);
}

char	*replace_withvar(char *str, t_list *g_env, t_list *l_var)
{
	char	*val;
	int		start;
	int		pos;
	t_list	*list;
	int		quote;

	list = NULL;
	pos = 0;
	start = 0;
	quote = 0;
	while (str[pos])
	{
		in_quote(str[pos], &quote);
		if (quote != '\'' && (str[pos] == '$' && (ft_isalpha(str[pos + 1])
			|| str[pos + 1] == '_' || str[pos + 1] == '$' || str[pos + 1] == '?'
			|| ft_isdigit(str[pos + 1]))))
		{
			ft_lstadd_back(&list, ft_lstnew(ft_substr(str, start, pos
							- start)));
			start = ++pos;
			while (ft_isalpha(str[pos]) || str[pos] == '_'
				|| ft_isdigit(str[pos]))
				pos++;
			if (start == pos)
				pos++;
			val = get_var(&str[start], pos - start, g_env, l_var);
			if (!val)
				val = "";
			ft_lstadd_back(&list, ft_lstnew(ft_strdup(val)));
			if (strncmp(&str[start], "?", 1) == 0)
				free(val);
			start = pos;
		}
		else
			pos++;
	}
	if (pos - start > 0)
		ft_lstadd_back(&list, ft_lstnew(ft_strdup(&str[start])));
	else if (pos == 0)
		return (ft_strdup(""));
	val = ft_lsttostr(list);
	ft_lstclear(&list, free);
	return (val);
}

char	*set_var(char *line, t_list *g_env, t_list **l_var)
{
	int		i;
	int		j;
	char	*word[2];
	int		quote;

	i = 0;
	j = 0;
	quote = 0;
	while (line[i])
	{
		if (in_quote(line[i], &quote))
			break ;
		while (line[i] == ' ')
			j = ++i;
		while (ft_isalpha(line[j]) || line[j] == '_' || (j > i
				&& ft_isdigit(line[j])))
			j++;
		if (!j || line[j] != '=')
			break ;
		word[1] = get_next_word(line, &i, ' ');
		word[0] = replace_withvar(word[1], g_env, *l_var);
		free(word[1]);
		if (!update_var(word[0], g_env) && !update_var(word[0], *l_var))
			ft_lstadd_back(l_var, ft_lstnew((void *)word[0]));
	}
	word[1] = replace_withvar(&line[i], g_env, *l_var);
	free(line);
	return (word[1]);
}
