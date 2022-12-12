#include "minshell.h"


// # include <readline/history.h>

// gcc test.c libft.a  -I/usr/local/opt/readline/include -L/usr/local/opt/readline/lib -lreadline
// void

// -L/usr/local/opt/readline/lib -lreadline

void ctrl_c()
{
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

void exit_whitout_arg(char **cmd)
{
	if(cmd[1] == NULL)
	{
		exit(0);
	}
	else
	{
		exit(ft_atoi(cmd[1]));
	}
}
void echo_cmd(char **cmd)
{
		int i = 1;
		int x = 0;

	check_getenv(cmd);
	while (cmd[i])
	{
		if (strncmp(cmd[1],"-n",2) == 0)
		{
			x = 1;
			cmd[i] = ft_strdup("");
		}
		else
		{
			printf("%s",cmd[i]);
			printf(" ");
		}
		i++;
	}
	if (x == 0)
    {
        printf("\n");
    }

	//  i = 1;
	// while(cmd[i])
	// {
	// 	printf("%s",cmd[i]);
	// 	i++;
	// }
	// printf("%s",getenv("HjjjOME"));
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
	if(cmd[1] == NULL)
	{
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

int main()
{
	char	**cmd;
	char	*line;
	// int z = 0;
	// char **

	
	ft_int_signal();
	while (1)
	{
	// 	int s;
		char s[100] ;
		line = readline("minishell % ");
		if (line == NULL)
		{
			//remember to clean the memory before exiting
			exit(0);
		}

		cmd = ft_splitquote(line);
		 if(cmd[0])
		 {
			 add_history(line);
		 }
		// if(cmd[0] != '\0' && cmd[0] != NULL)
		// {

			if( !cmd || !cmd[0])
			{
				continue;
			}
				// else
			if(cmd && ft_strncmp(cmd[0],"exit",4) == 0)
			{
					exit_whitout_arg(cmd);
			}
			
			else if(cmd && ft_strncmp(cmd[0],"echo",4) == 0)
			{
				echo_cmd(cmd);
			}
			else if(cmd && ft_strncmp(cmd[0],"pwd",3) == 0){
				getcwd(s, 100);
			printf("%s\n",getcwd(s,100));
			}
			else if(cmd && ft_strncmp(cmd[0],"cd",2) == 0){
				cd_cmd(cmd);
			}
		// 		// execve("/bin/ls", ,envp);

					// printf("%s    \n",cmd[1]);

				// print_env(cmd);

			
	}


		// scanf("%d", &s);
		// printf("%d\n",s);
	// }
}