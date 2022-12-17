#include "minishell.h"

char	*get_var(char *varname, int len, t_list *g_env, t_list *l_var)
{
	if (strcmp(varname, "?") == 0)
		return (ft_itoa(get_pipex()->status));
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
	while (str[pos])
	{
		if((str[pos] == '\'' && !in_quote(str[pos], &quote)) || !quote) {
			if (str[pos] == '$' && (ft_isalpha(str[pos + 1]) || str[pos + 1] == '_'
					|| str[pos + 1] == '$' || str[pos + 1] == '?'
					|| ft_isdigit(str[pos + 1])))
			{
				ft_lstadd_back(&list, ft_lstnew(ft_substr(str, start, pos - start)));
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
				start = pos;
			}
		}
		pos++;
	}
	if (pos - start > 0)
		ft_lstadd_back(&list, ft_lstnew(ft_strdup(&str[start])));
	else if (pos == 0)
		return (ft_strdup(""));
	val = listtostr(list);
	ft_lstclear(&list, free);
	return (val);
}

char	*set_var(char *line, t_list *g_env, t_list **l_var)
{
	int		i;
	int		j;
	char	*newline;
	char	*word;
	int		quote;

	i = 0;
	quote = 0;
	while (line[i])
	{
		if(in_quote(line[i], &quote)) 
			break;
		while (line[i] == ' ')
			i++;
		j = i;
		while (ft_isalpha(line[j]) || line[j] == '_' || (j > i
				&& ft_isdigit(line[j])))
			j++;
		if (line[j] != '=')
			break ;
		newline = get_next_word(line, &i, ' ');
		word = replace_withvar(newline, g_env, *l_var);
		free(newline);
		if (!update_var(word, g_env))
			if (!update_var(word, *l_var))
				ft_lstadd_back(l_var, ft_lstnew((void *)word));
		i++;
	}
	newline = replace_withvar(&line[i], g_env, *l_var);
	free(line);
	return (newline);
}

// void export_var() {

// }

void	unset_var(char **cmd, t_list **g_env, t_list **l_var)
{
	int i;
	int len;
	// int flag;
	t_list *g_point;
	t_list *l_point;
	t_list *prev;

	i = 0;
	while (cmd[i])
	{
		len = ft_strlen(cmd[i]);
		g_point = *g_env;
		while (g_point)
		{
			if (strncmp(g_point->content, cmd[i], len) == 0
				&& ((char *)g_point->content)[len] == '=')
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