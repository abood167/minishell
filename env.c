#include "minishell.h"

char	**update_envp(t_list *list)
{
	char	**arr;
	int		i;
	int		len;
	t_list	*node;

	node = list;
	len = 0;
	while(node) {
		if(ft_strchr((char*)node->content, '='))
			len++;
		node = node->next;
	}
	arr = (char **)malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (list)
	{
		if(ft_strchr((char*)list->content, '='))
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
		if(quote != '\'' && (str[pos] == '$' && (ft_isalpha(str[pos + 1]) || str[pos + 1] == '_'
					|| str[pos + 1] == '$' || str[pos + 1] == '?'
					|| ft_isdigit(str[pos + 1])))) {
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
		if (!j || line[j] != '=')
			break ;
		newline = get_next_word(line, &i, ' ');
		word = replace_withvar(newline, g_env, *l_var);
		free(newline);
		if (!update_var(word, g_env))
			if (!update_var(word, *l_var))
				ft_lstadd_back(l_var, ft_lstnew((void *)word));
	}
	newline = replace_withvar(&line[i], g_env, *l_var);
	free(line);
	return (newline);
}

//Sort

void sort_list(t_list *g_env)
{
	t_list *tmp;
	t_list *tmp2;
	char *tmp3;

	tmp = g_env;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strcmp(tmp->content, tmp2->content) > 0)
			{
				tmp3 = tmp->content;
				tmp->content = tmp2->content;
				tmp2->content = tmp3;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

void export_print(t_list *g_env){
	t_mini *m;
	int i;
	char *str;

	sort_list(g_env);
	m = get_mini();
	while (g_env)
	{
		ft_putstr_fd("declare -x ", m->out[1]);
		i = 0;
		while(((char *)g_env->content)[i] && ((char *)g_env->content)[i] != '=')
			i++;
		str = ft_substr((char *)g_env->content, 0, i);
		ft_putstr_fd(str, m->out[1]);
		if(((char *)g_env->content)[i] == '=') {
			ft_putstr_fd("=\"", m->out[1]);
			ft_putstr_fd(get_var(str, ft_strlen(str), g_env, NULL), m->out[1]);
			ft_putstr_fd("\"", m->out[1]);
		}
		free(str);
		ft_putstr_fd("\n", m->out[1]);
		g_env =	g_env->next;
	}
}

int invalid_var(char* str) {
	int i;

	i = 0;
	while(str[i] && (ft_isalpha(str[i]) || str[i] == '_' || (i && ft_isdigit(str[i])))) {
		i++;
	}
	if (str[i] == '\0')
		return 0;
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return 1;
}

void export_var(char **cmd, t_list **g_env, t_list **l_var) {
	int i;
	int j;
	char* temp[3];
	char** temp_s;
	int flag;

	i = 0;
	flag = 0;
	while (cmd[++i])
	{
		j = 0;
		while (ft_isalpha(cmd[i][j]) || cmd[i][j] == '_' || (j
				&& ft_isdigit(cmd[i][j])))
			j++;
		if (j && cmd[i][j] == '=')
		{
			temp[0] = ft_substr(cmd[i], 0, j);
			temp_s = ft_split(temp[0], '\0');
			unset_var(temp_s, g_env, l_var);
			ft_lstadd_back(g_env, ft_lstnew((void *)ft_strdup(cmd[i])));
			free(temp[0]);
			ft_freearray((void**)temp_s);
		}
		else if(!cmd[i][j])
		{
			temp[0] = get_var(cmd[i], ft_strlen(cmd[i]), *g_env, *l_var);
			if (temp[0]) {
				temp[1] = ft_strjoin(cmd[i], "=");
				temp[2] = ft_strjoin(temp[1], temp[0]);
				free(temp[1]);
			}
			else
				temp[2] = ft_strdup(cmd[i]);
			temp_s = ft_split(cmd[i], '\0');
			unset_var(temp_s, g_env, l_var);
			ft_lstadd_back(g_env, ft_lstnew((void *)temp[2]));
			ft_freearray((void**)temp_s);

		}
		else 
			flag = invalid_var(cmd[i]) || flag;
	}
	if(i == 1)
		export_print(*g_env);
	get_mini()->status = flag;
}

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
		if(invalid_var(cmd[i])) {
			i++;
			continue;
		}
		len = ft_strlen(cmd[i]);
		g_point = *g_env;
		while (g_point)
		{
			if (strncmp(g_point->content, cmd[i], len) == 0
				&& (((char *)g_point->content)[len] == '=' || !((char *)g_point->content)[len]))
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