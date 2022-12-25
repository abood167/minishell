#include "minishell.h"

static t_pipex	pipex; //change to pointer so you can call it one variable?

t_pipex* get_pipex() {
	return &pipex;
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
	char	**cmd;
	char	*line;
	char	**envp;
	t_list 	*g_env;
	t_list	*l_var;
	// t_list	*buffer;

	pipex.status = EXIT_SUCCESS;
	ft_int_signal();

	g_env = ft_arrtolst(env);
	l_var = NULL;
	// buffer = NULL;
	while (1)
	{
		envp = ft_lsttoarr(g_env);
		pipex_init(&pipex, envp);

		fix_dir();

		if (ac == 1) {
			line = readline("minishell % ");
			if (line == NULL)
			{
				//remember to clean the memory before exiting
				ft_putstr_fd("exit\n", 1);
				exit(0);
			}

			if(line[0])
				add_history(line);
			if(invalid_syntax(line, &pipex))
				continue;
			if(ft_strchr(line, '|'))
				line = pipe_shell(line, &pipex);
			if(!line)
				continue;
			line = set_var(line, g_env, &l_var); 
			line = strip_redirect(line, &pipex, 0); //handle bash: *: ambiguous redirect
			if(!line) //update status code
				continue; //If null could
			//Handle * before this
			cmd = ft_splitquote(line, ' '); //record which arr index is quote
			// Sort wildcard?./m //make ignore qoute
			cmd = ft_wildcard(cmd);
		}
		else
			cmd = ft_copyarr(&av[1]);

		if(!cmd || (cmd && !cmd[0]))
			continue;

		check_pipe(&pipex);
		
		if(ft_strcmp(cmd[0],"exit") == 0)
		{
			pipex.args = cmd;
			exit_command(&pipex);
		}
		else if(ft_strcmp(cmd[0],"echo") == 0)
			echo_cmd(cmd, pipex);
		else if(ft_strcmp(cmd[0],"pwd") == 0){
			//switch to print env
			line = getcwd(NULL, 0);
			ft_putstr_fd(line, pipex.out[1]);
			ft_putstr_fd("\n", pipex.out[1]);
			free(line);
		}
		else if(ft_strcmp(cmd[0],"cd") == 0)
			cd_cmd(cmd, g_env, l_var);
		else if(ft_strcmp(cmd[0],"unset") == 0)
			unset_var(&cmd[1], &g_env, &l_var);
		else if(ft_strcmp(cmd[0],"export") == 0)
			export_var(cmd, &g_env, &l_var);
		else {
			// printf("\x1B[31mexecuting command %s\x1B[0m\n", cmd[0]); //to remove
        	ft_lstadd_back(&pipex.pid, ft_lstnew((void*)(intptr_t)fork()));
			if (pipex.pid == 0)
				child(pipex, 0, cmd, envp);			
        	waitpid((pid_t)(intptr_t)ft_lstlast(pipex.pid)->content, &pipex.status, 0);
			pipex.status = WEXITSTATUS(pipex.status); //enviroment variable 
			// printf("stat: %d", pipex.status);
			//close pipes
		}
		ft_freearray((void**)envp);
		ft_freearray((void**)cmd);
		if (ac != 1 || pipex.is_child)
			break;
	}
	return (pipex.status);
}