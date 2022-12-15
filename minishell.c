#include "minshell.h"


// # include <readline/history.h>

// gcc test.c libft.a  -I/usr/local/opt/readline/include -L/usr/local/opt/readline/lib -lreadline
// void

// -L/usr/local/opt/readline/lib -lreadline


static t_pipex	pipex;

void ctrl_c()
{
	if(pipex.pid != 0)
		return ;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

void ft_int_signal()
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT,ctrl_c );
}

void check_getenv(char **cmd)
{
	int i = 1;
	while (cmd[i])
	{

		if(getenv(cmd[i]) != NULL)
		{
			cmd[i] = getenv(cmd[i]);
		}
		i++;
	}
	
}

int check_n(char *s)
{
	int i = 1;
	while(s[i] != '\0')
	{
		if(s[i] != 'n')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int ac(char **cmd)
{
	int i = 0;
	while(cmd[i])
	{
		i++;
	}
	return (i);
}

int check_digit(char *s)
{
	int i = 0;
	while(s[i] != '\0')
	{
		if(ft_isdigit(s[i]) == 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}
void exit_whitout_arg(char **cmd)
{

	if(cmd[1] == NULL)
	{
		exit(0);
	}
	// while(cmd[1] != '\0')
	// {
		if(check_digit(cmd[1]) == 0)
		{
			if (ac(cmd) > 2)
			{
				printf("exit\n");
				printf("minishell : exit : too many arguments\n");
				return ;
				
			}
			else
			{
				exit(ft_atoi(cmd[1]));
			}
		}
	// }
	printf("exit\n");
	printf("exit: %s: numeric argument required\n",cmd[1]);
	exit(0);	
}

void echo_cmd(char **cmd, t_pipex pipex)
{
	int i = 1;
	int x = 1;
	int t = 0;
		
	while (cmd[i])
	{
		if(cmd[i][0] == '-')
		{
			if(check_n(cmd[i]) == 0)
			{
				//possible leak, try free(cmd[i]) if found leak 
				// cmd[i] = ft_strdup("");
				x++;
				t = 1;

			}
			else
				break;
		}
		else
			break;
		
		i++;
	}
	i = x;

	while (cmd[i])
	{
		
		ft_putstr_fd(cmd[i],pipex.out[1]);
		if(cmd[(i + 1)] != NULL)
		{
			ft_putstr_fd(" ",pipex.out[1]);
		}
		i++;
	}
	
	if (t == 0)
    {
        ft_putstr_fd("\n",pipex.out[1]);
    }
}

// void get_get
void get_path(char **cmd)
{
	char *path;
	char *tmp;
	char **path_tab;
	int i = 0;

	path = getenv("PATH");
	path_tab = ft_split(path,':');
	while(path_tab[i])
	{
		tmp = ft_strjoin(path_tab[i],"/");
		tmp = ft_strjoin(tmp,cmd[0]);
		cmd[0] = tmp;
		i++;
	}
}


void cd_cmd(char **cmd)
{
	char *tmp;
	if(cmd[1] == NULL)
	{
		tmp = getenv("HOME");
		if(tmp == NULL)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return;
		}
		chdir(getenv("HOME"));
	}
	else
	{
		chdir(cmd[1]);
	}
}

void print_env(char **cmd)
{
	int i = 0;
	while(cmd[i])
	{
		printf("%s\n",cmd[i]);
		i++;
	}
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
	l_var = ft_lstnew(ft_strdup("?"));
	while (1)
	{
		envp = ft_lsttoarr(g_env);
		pipex_init(&pipex, envp);

		char s[100] ;
		while(!getcwd(s, 100)) //find out why 100
			cd_cmd(ft_split("cd ..", ' ')); //Not like bash

		if (ac == 1) {
			if(pipex.status == 130)
				printf("\n");
			line = readline("minishell % ");
			if (line == NULL)
			{
				//remember to clean the memory before exiting
				exit(0);
			}
			//Handle * before this
			cmd = ft_splitquote(line, ' '); //record which arr index is quote
			cmd = ft_wildcard(cmd);
			if(cmd[0])
			{
				add_history(line);
			}
		}
		else
			cmd = ft_copyarr(&av[1]);

		 //do replace var $ here
		 cmd = set_var(cmd, g_env, &l_var);
		 cmd = strip_redirect(cmd, &pipex);
		 if(!cmd)
		 	continue;
		// if(cmd[0] != '\0' && cmd[0] != NULL)
		// {

			check_pipe(&pipex);
			if( !cmd || !cmd[0])
			{
				continue;
			}
				// else
			if(cmd && ft_strcmp(cmd[0],"exit") == 0)
			{
				exit_whitout_arg(cmd);
			}
			else if(cmd && ft_strcmp(cmd[0],"echo") == 0)
			{
				echo_cmd(cmd, pipex);
			}
			else if(cmd && ft_strcmp(cmd[0],"pwd") == 0){
				getcwd(s, 100);
				printf("%s\n",getcwd(s,100));
			}
			else if(cmd && ft_strcmp(cmd[0],"cd") == 0){
				cd_cmd(cmd);
			}
			else if(cmd && ft_strcmp(cmd[0],"unset") == 0){
				unset_var(&cmd[1], &g_env, &l_var);
			}
			else if (ft_strcmp(cmd[0],"env") == 0){
				printarr(envp);
			}
			else {
				printf("\x1B[31mexecuting command %s\x1B[0m\n", cmd[0]); //to remove
				//Convert echo if redirection
				pipex.pid = fork();
				if (pipex.pid == 0)
					child(pipex, 0, cmd, envp);			
				waitpid(pipex.pid, &pipex.status, 0);
				pipex.status = WEXITSTATUS(pipex.status); //enviroment variable 
				//close pipes
			}
			//strip redirection


			
		// 		// execve("/bin/ls", ,envp);

					// printf("%s    \n",cmd[1]);

				// print_env(cmd);
		ft_freearray((void**)envp);
		if (ac != 1)
			break;		
	}


		// scanf("%d", &s);
		// printf("%d\n",s);
	// }
}