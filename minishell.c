/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbokhari <sbokhari@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 05:39:36 by sbokhari          #+#    #+#             */
/*   Updated: 2023/01/06 05:40:09 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_mini m;

t_mini	*get_mini(void)
{
	return (&m);
}

int mini_start(char **env) {
	m.status = EXIT_SUCCESS;
	ft_int_signal();
	m.g_env = ft_arrtolst(env);
	m.l_var = NULL;
	m.is_child = 0;
	m.buffer = NULL;
	m.doc_str = NULL;

	return 1;
}

void mini_cmd2(){
	int status;

	if (ft_strcmp(m.cmds[0], "unset") == 0)
		unset_var(&m.cmds[1], &m.g_env, &m.l_var);
	else if (ft_strcmp(m.cmds[0], "export") == 0)
		export_var(m.cmds, &m);
	else
	{
		ft_lstadd_back(&m.pid, ft_lstnew((void *)(intptr_t)fork()));
		if (ft_lstlast(m.pid)->content == 0)
			child(m, m.cmds, m.envp);
		waitpid((pid_t)(intptr_t)ft_lstlast(m.pid)->content, &status, 0);
		if (WEXITSTATUS(status) || (m.status != CTRL_C_E
				&& m.status != 131))
			m.status = WEXITSTATUS(status);
		else
			printf("\n");
	}
}

void mini_cmd(){
	check_pipe(&m);
	if (ft_strcmp(m.cmds[0], "exit"))
		m.status = 0;
	if (ft_strcmp(m.cmds[0], "exit") == 0)
	{
		m.args = m.cmds;
		exit_command(&m);
	}
	else if (ft_strcmp(m.cmds[0], "echo") == 0)
		echo_cmd(m.cmds, m);
	else if (ft_strcmp(m.cmds[0], "pwd") == 0)
	{
		free(m.line);
		m.line = getcwd(NULL, 0);
		ft_putstr_fd(m.line, m.out[1]);
		ft_putstr_fd("\n", m.out[1]);
		m.status = 0;
	}
	else if (ft_strcmp(m.cmds[0], "env") == 0)
		print_env();
	else if (ft_strcmp(m.cmds[0], "cd") == 0)
		cd_cmd(m.cmds, m.g_env, m.l_var);
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
	m.start = mini_start(env);
	while (!m.is_child || m.buffer)
	{
		if (!m.start)
			free_loop();
		mini_init(&m);
		if (ac == 1)
		{
			if(get_input())
				continue;
		}
		else
			m.cmds = ft_copyarr(&av[1]);
		if (!m.cmds || (m.cmds && !m.cmds[0]))
		{
			m.status = 0;
			continue ;
		}
		mini_cmd();
		if (ac != 1)
			break ;
	}
	free_loop();
	free_exit();
	return (m.status);
}
