#include "minishell.h"

static t_pipex	pipex;

t_pipex* get_pipex() {
	return &pipex;
}

// handle tab for "<" ie like "<tect.1"
// Test writing to place without permision
//pipe without spaces
// upgrade splitquotes for both | and ""
//Need to figure out sort order of env
//Export and set in pipe?
//Export and set $?
//Set cannot be mixed with other commands. If mixed, nothing happens
//handle for "d=55 c=$d"
//export alpha=5
//Var start with alpha or _
//do *
// when piping, fork self and not recall minishell
//Check last pipe have command
//fix ffff" "ffff
//unset 3asdasd
//exit prints exit
//test with symbolic link
//dont use env function?
//use getenv?
//bash: /home/zin: Is a directory
//command not found with number has different output
//exit status of execve
//<"|" cat | asd
int main(int ac, char **av, char **env)
{
	char	**cmd;
	char	*line;
	char	**envp;
	t_list 	*g_env;
	t_list	*l_var;

	pipex.status = EXIT_SUCCESS;
	ft_int_signal();

	g_env = ft_arrtolst(env);
	l_var = NULL;
	while (1)
	{
		envp = ft_lsttoarr(g_env);
		pipex_init(&pipex, envp);

		line = getcwd(NULL, 0);
		while(!line) //find out why 100
		{
			cd_cmd(ft_split("cd ..", ' ')); //Not like bash
			free(line);	
			line = getcwd(NULL, 0);
		}
		free(line);

		if (ac == 1) {
			if(pipex.status == 130)
				printf("\n");
			line = readline("minishell % ");
			if (line == NULL)
			{
				//remember to clean the memory before exiting
				exit(0);
			}
			//Quotation error and pipe error
			if(line[0] && line[0] != ' ')
				add_history(line);

			if(ft_strchr(line, '|'))
				line = pipe_shell(line, &pipex);
			//Handle * before this
			line = set_var(line, g_env, &l_var); 
			line = strip_redirect(line, &pipex);
			if (!line)
				continue;
			cmd = ft_splitquote(line, ' '); //record which arr index is quote
			// Sort wildcard?./m //make ignore qoute
			cmd = ft_wildcard(cmd);
		}
		else
			cmd = ft_copyarr(&av[1]);

		if(!cmd || (cmd && !cmd[0]))
		continue;
			

			check_pipe(&pipex);
			if( !cmd || !cmd[0])
			{
				continue;
			}
				// else
			if(cmd && ft_strcmp(cmd[0],"exit") == 0)
			{
				pipex.args = cmd;
				exit_command(&pipex);
			}
			else if(cmd && ft_strcmp(cmd[0],"echo") == 0)
			{
				echo_cmd(cmd, pipex);
			}
			else if(cmd && ft_strcmp(cmd[0],"pwd") == 0){
				//switch to print env
				line = getcwd(NULL, 0);
				ft_putstr_fd(line, pipex.out[1]);
				ft_putstr_fd("\n", pipex.out[1]);
				free(line);
			}
			else if(cmd && ft_strcmp(cmd[0],"cd") == 0){
				cd_cmd(cmd);
			}
			else if(cmd && ft_strcmp(cmd[0],"unset") == 0){
				unset_var(&cmd[1], &g_env, &l_var);
			}
			else {
				// printf("\x1B[31mexecuting command %s\x1B[0m\n", cmd[0]); //to remove
				pipex.pid = fork();
				if (pipex.pid == 0)
					child(pipex, 0, cmd, envp);			
				waitpid(pipex.pid, &pipex.status, 0); //text exucting non executable
				pipex.status = WEXITSTATUS(pipex.status); //enviroment variable 
				// printf("stat: %d", pipex.status);
				//close pipes
			}

		ft_freearray((void**)envp);
		if (ac != 1 || pipex.is_child)
			break;
	}

	return (pipex.status);
}