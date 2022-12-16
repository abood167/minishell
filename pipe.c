#include "minishell.h"

char	*pipe_shell(char *line, t_pipex *pipex)
{
	int i;
    char **pipe_line;

	pipe_line = ft_split(line, '|');
    free(line);
    line = NULL;
    i = 0;
    while(pipe_line[i]){
        if (pipe_line[i  + 1])
            pipe(pipex->out); //error handle?
        pipex->pid = fork();
        if (pipex->pid == 0) {
            pipex->is_child = 1;
            break;
        }
        if(pipex->in != 0)
            close(pipex->in);
        if(pipex->out[1] != 1)
            close(pipex->out[1]);
        pipex->in = pipex->out[0];
		pipex->out[1] = 1;
        i++;
    }
    if (pipe_line[i])
        line = ft_strdup(pipe_line[i]);
    ft_freearray((void **)pipe_line);
    if(pipex->pid != 0) {  
        waitpid(pipex->pid, &pipex->status, 0);
        pipex->status = WEXITSTATUS(pipex->status);
    }
    return line;
}