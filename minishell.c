#include "minishell.h"

static t_mini	m; //change to pointer so you can call it one variable?

t_mini* get_mini() {
	return &m;
}

void fix_dir() {
	char *line;

	line = getcwd(NULL, 0);
	while(!line)
	{
		cd_cmd(ft_split("cd ..", ' '), NULL, NULL); //Not like bash
		free(line);	
		line = getcwd(NULL, 0);
	}
	free(line);
}

void free_loop() {
	ft_freearray((void**)m.envp);
	ft_freearray((void**)m.cmds);
	ft_freearray((void**)m.paths);
	ft_lstclear(&m.pid, NULL);
}

void free_exit() {
	ft_lstclear(&m.g_env, free);
	ft_lstclear(&m.l_var, free);
}

//check quote, pipe, && and || validity
//upgrade splitquotes for both | and ""
//Need to figure out sort order of env
//update status in more places
//exit status for other errors
//exit status of execve
//Set cannot be mixed with other commands. If mixed, nothing happens
//export alpha=5
//exit prints exit
//test with symbolic link
//handle for execution and redirect? bash: /home/zin: Is a directory
//command not found with number has different output
// <<lm | <<lm  //Solution do pipe without forking in function. Make it handle | && || 
// echo <d <<lm  (does here_doc first before error)
// <<should be done before pipe and &&
//bash-3.2$ true || (echo aaa && echo bbb)
//bash-3.2$ false || (echo aaa && echo bbb)
//bash-3.2$ false && echo a && echo b
//bash-3.2$ true || echo a && echo b
int main(int ac, char **av, char **env)
{
	// t_list	*buffer;

	m.status = EXIT_SUCCESS;
	ft_int_signal();

	m.g_env = ft_arrtolst(env);
	m.l_var = NULL;
	// buffer = NULL;
	while (!m.is_child)
	{
		m.envp = ft_lsttoarr(m.g_env);
		mini_init(&m, m.envp);

		fix_dir();

		if (ac == 1) {
			m.line = readline("minishell % ");
			if (m.line == NULL)
			{
				//remember to clean the memory before exiting
				ft_putstr_fd("exit\n", 1);
				exit(0);
			}

			if(m.line[0])
				add_history(m.line);
			if(invalid_syntax(m.line, &m))
				continue;
			strip_heredoc(m.line, &m); //handle bash: *: ambiguous redirect
			if(m.status != 0)
				continue;
			if(ft_strchr(m.line, '|'))
				m.line = pipe_shell(m.line, &m);
			if(!m.line)
				continue;
			m.line = set_var(m.line, m.g_env, &m.l_var); 
			m.line = strip_redirect(m.line, &m, 0); //handle bash: *: ambiguous redirect
			if(!m.line) //update status code
				continue; //If null could
			//Handle * before this
			m.cmds = ft_splitquote(m.line, ' '); //record which arr index is quote
			// Sort wildcard?./m //make ignore qoute
			m.cmds = ft_wildcard(m.cmds);
			free(m.line);
		}
		else
			m.cmds = ft_copyarr(&av[1]);

		if(!m.cmds || (m.cmds && !m.cmds[0]))
			continue;

		check_pipe(&m);
		
		if(ft_strcmp(m.cmds[0],"exit") == 0)
		{
			m.args = m.cmds;
			exit_command(&m);
		}
		else if(ft_strcmp(m.cmds[0],"echo") == 0)
			echo_cmd(m.cmds, m);
		else if(ft_strcmp(m.cmds[0],"pwd") == 0){
			//switch to print env
			m.line = getcwd(NULL, 0);
			ft_putstr_fd(m.line, m.out[1]);
			ft_putstr_fd("\n", m.out[1]);
			free(m.line);
		}
		else if(ft_strcmp(m.cmds[0],"env") == 0)
			printarr(m.envp);
		else if(ft_strcmp(m.cmds[0],"cd") == 0)
			cd_cmd(m.cmds, m.g_env, m.l_var);
		else if(ft_strcmp(m.cmds[0],"unset") == 0)
			unset_var(&m.cmds[1], &m.g_env, &m.l_var);
		else if(ft_strcmp(m.cmds[0],"export") == 0)
			export_var(m.cmds, &m.g_env, &m.l_var);
		else {
        	ft_lstadd_back(&m.pid, ft_lstnew((void*)(intptr_t)fork()));
			if (ft_lstlast(m.pid)->content == 0) 
				child(m, m.cmds, m.envp);		
        	waitpid((pid_t)(intptr_t)ft_lstlast(m.pid)->content, &m.status, 0);
			m.status = WEXITSTATUS(m.status);
			//close pipes
		}
		free_loop();
		if (ac != 1 || m.is_child)
			break;
		//flush readline?
	}
	free_exit();
	return (m.status);
}