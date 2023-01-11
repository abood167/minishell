/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 05:39:35 by sbokhari          #+#    #+#             */
/*   Updated: 2023/01/10 08:20:42 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_var(char *var, t_list *g_env)
{
	size_t	len;

	len = (size_t)ft_strchr(var, '=') - (size_t)var;
	while (g_env)
	{
		if (!ft_strncmp((char *)g_env->content, var, len + 1)
			|| (!ft_strncmp((char *)g_env->content, var, len)
				&& ((char *)g_env->content)[len] == '\0'))
		{
			free(g_env->content);
			g_env->content = var;
			return (1);
		}
		g_env = g_env->next;
	}
	return (0);
}

void	replace_withvar2(char *str, int *start, int *pos, t_list **list)
{
	char	*val;

	ft_lstadd_back(list, ft_lstnew(ft_substr(str, *start, *pos - *start)));
	*start = ++*pos;
	while (ft_isalpha(str[*pos]) || str[*pos] == '_' || ft_isdigit(str[*pos]))
		(*pos)++;
	if (*start == *pos)
		(*pos)++;
	val = get_var(&str[*start], *pos - *start, get_mini()->g_env,
			get_mini()->l_var);
	if (!val)
		val = "";
	ft_lstadd_back(list, ft_lstnew(ft_strdup(val)));
	if (strncmp(&str[*start], "?", 1) == 0)
		free(val);
	*start = *pos;
}

char	*replace_withvar(char *str)
{
	char	*val;
	int		start;
	int		pos;
	t_list	*list;
	int		quote;

	list = init_zero(&pos, &start, &quote, NULL);
	while (str[pos])
	{
		in_quote(str[pos], &quote);
		if (quote != '\'' && (str[pos] == '$' && (ft_isalpha(str[pos + 1])
					|| str[pos + 1] == '_' || str[pos + 1] == '$'
					|| str[pos + 1] == '?'
					|| ft_isdigit(str[pos + 1]))))
			replace_withvar2(str, &start, &pos, &list);
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
	char	*word[2];
	int		quote;

	init_zero(&i, &quote, NULL, NULL);
	while (line[i])
	{
		if (in_quote(line[i], &quote))
			break ;
		while (line[i] == ' ')
			++i;
		if (invalid_var(&line[i], 1))
			break ;
		word[1] = get_next_word(line, &i, ' ');
		word[0] = replace_withvar(word[1]);
		free(word[1]);
		if (!update_var(word[0], g_env) && !update_var(word[0], *l_var))
			ft_lstadd_back(l_var, ft_lstnew((void *)word[0]));
	}
	word[1] = replace_withvar(&line[i]);
	free(line);
	return (word[1]);
}
