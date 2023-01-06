/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbokhari <sbokhari@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 05:39:35 by sbokhari          #+#    #+#             */
/*   Updated: 2023/01/06 05:40:09 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_print(t_list *g_env)
{
	t_mini	*m;
	int		i;
	char	*str;

	sort_lst(g_env);
	m = get_mini();
	while (g_env)
	{
		ft_putstr_fd("declare -x ", m->out[1]);
		i = 0;
		while (((char *)g_env->content)[i]
			&& ((char *)g_env->content)[i] != '=')
			i++;
		str = ft_substr((char *)g_env->content, 0, i);
		ft_putstr_fd(str, m->out[1]);
		if (((char *)g_env->content)[i] == '=')
		{
			ft_putstr_fd("=\"", m->out[1]);
			ft_putstr_fd(get_var(str, ft_strlen(str), g_env, NULL), m->out[1]);
			ft_putstr_fd("\"", m->out[1]);
		}
		free(str);
		ft_putstr_fd("\n", m->out[1]);
		g_env = g_env->next;
	}
}

int	invalid_var(char *str, int set_var)
{
	int	i;

	i = 0;
	while (str[i] && (ft_isalpha(str[i]) || str[i] == '_' || (i
				&& ft_isdigit(str[i]))))
	{
		i++;
	}
	if(!set_var) {
		if (str[i] == '\0')
			return (0);
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	else if (i && str[i] == '=')
		return (0);
	return (1);
}

void	export_var(char **cmd, t_list **g_env, t_list **l_var)
{
	int		i;
	int		j;
	char	*temp[3];
	char	**temp_s;
	int		flag;

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
			ft_freearray((void **)temp_s);
		}
		else if (!cmd[i][j])
		{
			temp[0] = get_var(cmd[i], ft_strlen(cmd[i]), *g_env, *l_var);
			if (temp[0])
			{
				temp[1] = ft_strjoin(cmd[i], "=");
				temp[2] = ft_strjoin(temp[1], temp[0]);
				free(temp[1]);
			}
			else
				temp[2] = ft_strdup(cmd[i]);
			temp_s = ft_split(cmd[i], '\0');
			unset_var(temp_s, g_env, l_var);
			ft_lstadd_back(g_env, ft_lstnew((void *)temp[2]));
			ft_freearray((void **)temp_s);
		}
		else
			flag = invalid_var(cmd[i], 0) || flag;
	}
	if (i == 1)
		export_print(*g_env);
	get_mini()->status = flag;
}
