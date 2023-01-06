/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbokhari <sbokhari@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 05:39:34 by sbokhari          #+#    #+#             */
/*   Updated: 2023/01/06 05:39:55 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_n(char *s)
{
	int	i;

	i = 1;
	while (s[i] != '\0')
	{
		if (s[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	echo_cmd(char **cmd, t_mini m)
{
	int	i;
	int	t;

	i = 0;
	t = 0;
	while (cmd[++i] && cmd[i][0] == '-' && cmd[i][1] == 'n'
		&& check_n(cmd[i]) == 0)
		t = 1;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], m.out[1]);
		if (cmd[(i + 1)] != NULL)
			ft_putstr_fd(" ", m.out[1]);
		i++;
	}
	if (t == 0)
		ft_putstr_fd("\n", m.out[1]);
}

void	cd_cmd(char **cmd, t_list *g_env, t_list *l_var)
{
	get_mini()->status = 1;
	if (cmd[1] == NULL)
	{
		if (!get_var("HOME", 4, g_env, l_var))
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		else if (get_var("HOME", 4, g_env, l_var)[0] && chdir(get_var("HOME", 4,
						g_env, l_var)) < 0)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			perror(get_var("HOME", 4, g_env, l_var));
		}
		else
			get_mini()->status = 1;
	}
	else if (cmd[2] != NULL)
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	else if (!cmd[1][0])
		get_mini()->status = 1;
	else if (chdir(cmd[1]) < 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(cmd[1]);
	}
	else
		get_mini()->status = 1;
}

void	print_env(void)
{
	t_mini *m;
	char **str;

	m = get_mini();
	str = m->envp;
	while (*str)
	{
		ft_putstr_fd(*str, m->out[1]);
		ft_putstr_fd("\n", m->out[1]);
		str++;
	}
}
