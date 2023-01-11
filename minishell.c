/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 05:39:36 by sbokhari          #+#    #+#             */
/*   Updated: 2023/01/11 12:45:11 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_mini	g_m;

t_mini	*get_mini(void)
{
	return (&g_m);
}

int	mini_start(char **env)
{	
	char *cmd[3];

	g_m.status = EXIT_SUCCESS;
	ft_int_signal();
	g_m.g_env = ft_arrtolst(env);
	g_m.l_var = NULL;
	g_m.is_child = 0;
	g_m.buffer = NULL;
	g_m.doc_str = NULL;
	cmd[1] = "OLDPWD";
	cmd[2] = NULL;
	unset_var(&cmd[1], &g_m.g_env, &g_m.l_var);
	export_var(cmd, &g_m);
	return (1);
}

void	mini_cmd2(void)
{
	int	status;

	if (ft_strcmp(g_m.cmds[0], "unset") == 0)
		unset_var(&g_m.cmds[1], &g_m.g_env, &g_m.l_var);
	else if (ft_strcmp(g_m.cmds[0], "export") == 0)
		export_var(g_m.cmds, &g_m);
	else
	{
		ft_lstadd_back(&g_m.pid, ft_lstnew((void *)(intptr_t)fork()));
		if (ft_lstlast(g_m.pid)->content == 0)
			child(g_m, g_m.cmds, g_m.envp);
		waitpid((pid_t)(intptr_t)ft_lstlast(g_m.pid)->content, &status, 0);
		if (WEXITSTATUS(status) || (g_m.status != CTRL_C_E
				&& g_m.status != 131))
			g_m.status = WEXITSTATUS(status);
		else
			printf("\n");
	}
}

void	mini_cmd(void)
{
	check_pipe(&g_m);
	if (ft_strcmp(g_m.cmds[0], "exit"))
		g_m.status = 0;
	if (ft_strcmp(g_m.cmds[0], "exit") == 0)
	{
		g_m.args = g_m.cmds;
		exit_command(&g_m);
	}
	else if (ft_strcmp(g_m.cmds[0], "echo") == 0)
		echo_cmd(g_m.cmds, g_m);
	else if (ft_strcmp(g_m.cmds[0], "pwd") == 0)
	{
		free(g_m.line);
		g_m.line = getcwd(NULL, 0);
		ft_putstr_fd(g_m.line, g_m.out[1]);
		ft_putstr_fd("\n", g_m.out[1]);
		g_m.status = 0;
	}
	else if (ft_strcmp(g_m.cmds[0], "env") == 0)
		print_env();
	else if (ft_strcmp(g_m.cmds[0], "cd") == 0)
		cd_cmd(g_m.cmds, g_m.g_env, g_m.l_var);
	else
		mini_cmd2();
}

//check quote, pipe, && and || validity
//Need to figure out sort order of env
//test with symbolic link
// <<lm || <<lm
//Test on mac ctrl+D  on here_doc and incomplete syntax (ie unclosed quotes)
// echo a (echo b)
// ()
// asd (
// (echo a && echo b) && sleep 2 && echo c | cat -n && cd ..
// (echo a)) //incorrect syntax error
int	main(int ac, char **av, char **env)
{
	g_m.start = mini_start(env);
	while (!g_m.is_child || g_m.buffer)
	{
		if (!g_m.start)
			free_loop();
		mini_init(&g_m);
		if (ac == 1)
		{
			if (get_input())
				continue ;
		}
		else
			g_m.cmds = ft_copyarr(&av[1]);
		if (!g_m.cmds || (g_m.cmds && !g_m.cmds[0]))
		{
			g_m.status = 0;
			continue ;
		}
		mini_cmd();
		if (ac != 1)
			break ;
	}
	free_loop();
	free_exit();
	return (g_m.status);
}
