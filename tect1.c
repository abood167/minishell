#include <unistd.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

// -L/usr/local/opt/readline/lib -lreadline

int main(int ac, char **av, char **env)
{
	char	**cmd;
	char	*line;
	int		pid;

	while (42)
	{
	// 	int s;
		line = readline("minishell %-> ");
		 add_history(line);
		// chdir("Users/abin-saa")
		// cmd = malloc(sizeof(char *) * 2);
		// cmd[0] = strdup(line);
		// cmd[1] = NULL;
		// pid = fork();
		// if (pid == 0)
		// {
		// 	execvp(cmd[0], cmd);
		// 	// printf("test");
		// }
		// printf("%d",s);
		// scanf("%d", &s);
		
		//


		wait(NULL);
		// printf("%d\n",s);
	}
	return (0);
}
// }


