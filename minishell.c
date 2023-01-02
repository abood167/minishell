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
	m.envp = NULL;
	m.cmds = NULL;
	m.paths = NULL;
	ft_lstclear(&m.pid, NULL);
	free(m.line);
	m.line = NULL;
	alt_close(&m.in);
	alt_close(&m.out[0]);
	alt_close(&m.out[1]);
}

void free_exit() {
	ft_lstclear(&m.pid, NULL);
	ft_lstclear(&m.buffer, free);
	ft_lstclear(&m.g_env, free);
	ft_lstclear(&m.l_var, free);
	rl_clear_history();
}

// wildcard in quotes
//check quote, pipe, && and || validity
//Need to figure out sort order of env
//test with symbolic link
// <<lm || <<lm  
//bash-3.2$ true || (echo aaa && echo bbb)
//bash-3.2$ false || (echo aaa && echo bbb)
//bash-3.2$ false && echo a && echo b
//bash-3.2$ true || echo a && echo b
//Test on mac ctrl+D  on here_doc and incomplete syntax (ie unclosed quotes)
// echo a (echo b)
// ()
// asd (
// (echo a && echo b) && sleep 2 && echo c | cat -n && cd ..
// (echo a)) //incorrect syntax error
int main(int ac, char **av, char **env)
{
	int status;
	int syntax;
	int start;

	m.status = EXIT_SUCCESS;
	ft_int_signal();

	m.g_env = ft_arrtolst(env);
	m.l_var = NULL;
	m.is_child = 0;
	start = 1;
	m.buffer = NULL;
	while (!m.is_child || m.buffer)
	{
		if(!start)
			free_loop();
		start = 0;
		m.envp = update_envp(m.g_env);
		mini_init(&m, m.envp);

		fix_dir();

		if (ac == 1) {
			if(!m.buffer) {
				m.line = readline("minishell % ");
				if (m.line == NULL)
				{
					//remember to clean the memory before exiting
					ft_putstr_fd("exit\n", 1);
					exit(0);
				}
				if(m.line[0])
					add_history(m.line);
				syntax = 2;
				while(syntax == 2)
					syntax = invalid_syntax(m.line, &m);
				if(syntax)
					continue;
				if(strip_heredoc(m.line, &m))
					continue;
			}
			if(shell_conditions(&m))
				continue;
			if(ft_strchr(m.line, '|')) //do a better method for check
				m.line = pipe_shell(m.line, &m);
			if(!m.line)  //check for if start with braces
				continue;
			m.line = set_var(m.line, m.g_env, &m.l_var); 
			m.line = strip_redirect(m.line, &m, 0);
			if(!m.line) //update status code
				continue; //If null could
			m.cmds = ft_splitquote(m.line, ' '); //record which arr index is quote
			// Sort wildcard? //make ignore qoute (need put before split)
			m.cmds = ft_wildcard(m.cmds);
		}
		else
			m.cmds = ft_copyarr(&av[1]);

		if(!m.cmds || (m.cmds && !m.cmds[0]))
			continue;

		check_pipe(&m);
		
		m.status = 0;
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
			m.line = NULL;
			m.status = 0;
		}
		else if(ft_strcmp(m.cmds[0],"env") == 0)
			print_env();
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
			waitpid((pid_t)(intptr_t)ft_lstlast(m.pid)->content, &status, 0);
			if(m.status != 130 && m.status != 131)
				m.status = WEXITSTATUS(status);
			else
				printf("\n");
			//close pipes
		}
		if (ac != 1)
			break;
		//flush readline?
	}
	free_loop();
	free_exit();
	return (m.status);
}